#!/bin/bash
# Migration script to clean up old test files and activate new gtest-based tests

echo "Spiced Test Suite Migration"
echo "============================"
echo ""
echo "This script will:"
echo "1. Backup old test files to old_tests/ directory"
echo "2. Remove old test files from test/ directory"
echo "3. Activate the new gtest makefile"
echo ""
read -p "Continue? (y/n) " -n 1 -r
echo ""

if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Migration cancelled."
    exit 1
fi

# Create backup directory
mkdir -p old_tests

# Move old test files to backup
echo "Backing up old test files..."
mv -v test.cc test.h old_tests/ 2>/dev/null
mv -v probmodels.cc probmodels.h old_tests/ 2>/dev/null
mv -v psmodels.cc psmodels.h old_tests/ 2>/dev/null
mv -v ptmodels.cc ptmodels.h old_tests/ 2>/dev/null
mv -v mavhmodels.cc mavhmodels.h old_tests/ 2>/dev/null
mv -v mavpsmodels.cc mavpsmodels.h old_tests/ 2>/dev/null
mv -v mavptmodels.cc mavptmodels.h old_tests/ 2>/dev/null
mv -v testmavtrans.cc testmavtrans.h old_tests/ 2>/dev/null
mv -v netfunc.cc netfunc.h old_tests/ 2>/dev/null

# Backup old makefile
echo "Backing up old makefile..."
mv -v makefile old_tests/makefile.original 2>/dev/null

# Activate new makefile
echo "Activating new gtest makefile..."
mv -v makefile.gtest makefile

echo ""
echo "Migration complete!"
echo ""
echo "Old test files backed up to: old_tests/"
echo "New makefile activated"
echo ""
echo "To build and run tests:"
echo "  make"
echo "  make test"
echo ""
echo "To restore old setup:"
echo "  cp old_tests/makefile.original makefile"
echo "  cp old_tests/*.cc old_tests/*.h ."
