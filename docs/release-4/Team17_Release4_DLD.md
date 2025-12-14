# Release 4 – Persistent Repository Extension

Release 4 extends the Release 3 behavior-focused design with disk-backed storage. The same UI → Logic → Repository stack now adds a file behind the Repository so that every `Order` survives application restarts. The sections below mirror the official DLD guide items (1‑10) and show how the new Repository integrates without changing the public architecture.

---

## 1. System Overview & Architectural Context
- **Dual storage model**: Logic always works with the Repository’s in-memory dynamic array; the Repository mirrors that state to a CSV-like text file on shutdown.
- **Startup path**: On boot the Repository loads the file, validates each line, re-creates `Order` objects, and exposes them to `StudioManager`.
- **Runtime path**: UI → `StudioManager` → Repository; no class outside Repository touches the file.
- **Shutdown path**: `StudioManager` triggers `Repository::saveAll`, which rewrites the file with a canonical representation.
- **Corruption protection**: malformed lines are skipped during `loadAll`, preventing invalid file content from polluting memory.

---

## 2. UML Class Diagram Updates
The Release 3 UML remains valid. Only `OrderRepository` gains four persistence methods while relationships stay unchanged:

| Class | New / Adjusted Methods |
| --- | --- |
| `OrderRepository` | `loadAll()`, `saveAll()`, `parseLine(line)`, `toLine(order)` |

No other associations change; UI still depends on `StudioManager`, `StudioManager` depends on Repository + entities, and Repository alone communicates with the file.

---

## 3. Class Specifications (Repository Focus)

| Attribute | Description |
| --- | --- |
| `Order* data` | Dynamic array that stores `Order` objects in memory. |
| `std::size_t count` | Current number of valid `Order` entries. |
| `std::size_t capacity` | Allocated size of `data`. Always `>= count`. |
| `std::string filePath` | Absolute/relative path of the storage file. |

| Method | Purpose | Key Behavioral Constraints |
| --- | --- | --- |
| `loadAll()` | Populate memory from file. | Never throws for malformed lines; resets `count`; skips invalid records. |
| `saveAll()` | Rewrite file from memory. | Truncates target file each run; only called after successful UI session. |
| `parseLine(line)` | Validate + convert one record. | Requires correct field count; rejects invalid enum/bool tokens. |
| `toLine(order)` | Serialize an order to text. | Emits canonical format so load/save remain symmetric. |

---

## 4. Interfaces & Abstractions
- **Repository API**: `StudioManager` only sees `add`, `tryGet`, `toVector`, `loadAll`, `saveAll`. Memory layout and file syntax stay hidden.
- **Implicit contract**: Repository guarantees stable indices during one run and enforces `capacity >= count`. Logic trusts that invariants even though the physical storage (array vs. file) can evolve.

---

## 5. Function Responsibilities

| Function | Inputs | Outputs | Responsibility Notes |
| --- | --- | --- | --- |
| `loadAll()` | Storage file on disk | Populated dynamic array | Opens file if it exists, reads line by line, populates array, and ignores malformed data instead of raising an exception. |
| `saveAll()` | In-memory array | Serialized file | Rebuilds a fresh file by serializing every order; ensures directory exists before writing. |
| `parseLine(const std::string&)` | Raw line | `Order` object (by out parameter) | Splits on `;`, validates field count, converts status + express flag, and returns false if anything violates the schema. |
| `toLine(const Order&)` | `Order` object | Canonical line string | Produces `customer;photos;type;status;express` so the result can be loaded verbatim next run. |

---

## 6. Operation Flow
- **Startup Flow**
  1. File opened (if present) and read into memory.
  2. Each line → `parseLine`.
  3. Valid orders appended to the Repository array (which grows dynamically as needed).
  4. Logic/UI work with reconstructed state.
- **Shutdown Flow**
  1. `StudioManager` calls `saveAll`.
  2. Repository serializes every `Order` via `toLine`.
  3. File is truncated and rewritten so disk matches memory exactly.

Both flows keep UI oblivious to persistence concerns.

---

## 7. Validation Rules (Release 4 Additions)

| Validation Rule | Enforcement Layer | Reason |
| --- | --- | --- |
| File line contains exactly 5 delimited fields | Repository (`parseLine`) | Prevents partially written records from entering memory. |
| Status token must match known enums (`PENDING`, `PROCESSING`, `IN_PROGRESS`, `COMPLETED`) | Repository (`parseLine`) | Keeps state machine valid after reload. |
| Express flag must be one of `Y/N/true/false/0/1` | Repository (`parseLine`) | Avoids unintended surcharge states. |
| Empty or whitespace-only lines skipped silently | Repository (`loadAll`) | Allows human-friendly spacing without breaking load. |
| Non-existent file → empty repository | Repository (`loadAll`) | First launch works even without seed data. |

---

## 8. Traceability Matrix

| SRS Requirement | Release 4 Design Element |
| --- | --- |
| “Persist orders between sessions” | `OrderRepository::saveAll()` + `loadAll()` |
| “Handle malformed file input gracefully” | `parseLine()` returning `false` to skip invalid rows |
| “Support repository growth without fixed limit” | Dynamic array (`ensureCapacity`, `data/count/capacity`) |
| “Connect UI → Logic → Repository → File” | `StudioManager` now owns an `OrderRepository&` and calls `saveAll` on shutdown |
| “Full rewrite on save” | `saveAll()` truncates file and writes every record |

---

## 9. Preconditions & Postconditions

| Method | Preconditions | Postconditions | Validation Level | Explanation |
| --- | --- | --- | --- | --- |
| `loadAll()` | Storage path is readable (if file exists). | `count` reflects number of valid rows; invalid lines skipped; memory contains only validated orders. | Repository | Guards memory from corrupt disk input without propagating user-facing errors. |
| `saveAll()` | Directory is writable; Repository already populated. | File rewritten with one line per order; disk mirrors memory. | Repository | Ensures persistence contract before application exits. |
| `parseLine(line)` | `line` is non-empty string. | Returns true only if the order matches schema and enum rules; output `Order` initialized. | Repository | Centralizes all file-format validation. |
| `toLine(order)` | `order` contains valid data. | Returns canonical string that `parseLine` accepts verbatim. | Repository | Guarantees symmetric serialization/deserialization. |

---

## 10. Error & Exception Handling Policy

| Scenario | Behavior | User Visibility |
| --- | --- | --- |
| File missing at startup | `loadAll` treats repository as empty; no exception thrown. | None – UI just shows empty list. |
| Malformed line during load | `parseLine` returns false; line skipped. | None – optional log only. |
| File cannot be opened for save | Repository throws `RepositoryException`; `main()` catches and prints non-technical warning. | UI sees “Warning: Unable to save data…” after exit. |
| Runtime validation failures (Release 3 rules) | Still thrown as `BusinessRuleException` / `InputValidationException` in Logic/UI. | UI prints friendly message (unchanged from Release 3). |

---

## Conclusion
Release 4 keeps the behavioral guarantees from Release 3 and layers a resilient persistence mechanism underneath. The Repository now owns the file lifecycle, shields Logic from corrupted input, and guarantees that every in-memory change reaches disk during shutdown. Thus Releases 2–4 form a single, coherent architecture: UI handles interaction, Logic enforces business rules, Repository mediates data lifetime, and the file preserves state across runs.


