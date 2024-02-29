cc test_qsplit.c ../parse_split.c ../parse_split_utils.c ../libft/libft.a -I ../ -o parse_split_test

echo Test1:

echo Split this first

echo ""

./parse_split_test "Split this first"

echo ""

echo Test2:

echo Split \"this\" second

echo ""

./parse_split_test "Split "this" second"

echo ""

echo Test3:

echo Split \'this\' second

echo ""

./parse_split_test "Split 'this' second"