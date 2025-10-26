#!/usr/bin/env bash
set -euo pipefail

echo "Building Photo Studio Management System..."

# Build the project
cd "$(dirname "$0")/.."
mkdir -p build
cd build
cmake .. > /dev/null 2>&1
make > /dev/null 2>&1

if [ ! -f "./photo_studio" ]; then
  echo "❌ Build failed - executable not found"
  exit 1
fi

echo "✅ Build successful"
echo "✅ Photo Studio Management System is ready to run"
echo ""
echo "To run the application:"
echo "  ./build/photo_studio"
