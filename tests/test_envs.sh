#!/bin/bash

echo "Creating test .env files..."
cat > test1.env << EOF
DB_HOST=localhost
DB_PORT=5432
API_KEY=abc123
EOF

cat > test2.env << EOF
DB_HOST=localhost
DB_PORT=5432
API_KEY=abc123
NEW_KEY=new_value
EXTRA_KEY=extra_value
EOF

echo "✅ Test files created"

echo -e "\n🔍 Testing colored compare output:"
../bin/envsync compare test1.env test2.env

echo -e "\n🔄 Testing backup functionality:"
../bin/envsync backup test1.env

echo -e "\n📊 Testing interactive compare (will prompt for input):"
echo "Press 'n' when prompted to skip sync"
../bin/envsync compare-i test1.env test2.env

echo -e "\n🔄 Testing interactive sync (will prompt for input):"
echo "Press 'y' when prompted to create backup, then 'y' to sync"
../bin/envsync sync-i test1.env test2.env

echo -e "\n🔍 Verifying sync results:"
../bin/envsync compare test1.env test2.env

echo -e "\n🧹 Cleaning up test files..."
rm -f test1.env test2.env test1.env.backup.*

echo "✅ Test completed!" 