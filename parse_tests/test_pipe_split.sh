#For the moment, the init_command_array function should be commented out to run this test

cc test_pipe_split.c ../parse_split.c ../parse_split_utils.c ../parsing/parse_split_pipes.c ../parse_init.c ../parse_errors.c ../errors.c ../libft/libft.a -I ../ -o pipe_split_test

echo Test1

echo Split this first

./pipe_split_test "Split this first"

echo ""

echo Test2

echo "Split|this|second"

./pipe_split_test "Split|this|second"

echo ""

echo Test3

echo "Operator error || test"

./pipe_split_test "Operator error || test"

echo ""

echo Test4

echo "More than two ||| pipe error test"

./pipe_split_test "More than two ||| pipe error test"

echo ""

echo Test5

echo "| Testing starting with pipe"

./pipe_split_test "| Testing starting with pipe"

echo ""

echo Test6

echo "Testing ending with pipe |    "

./pipe_split_test "Testing ending with pipe |    "

echo ""

echo Test7

echo "Testing pipe 'between | quotes' | and out"

./pipe_split_test "Testing pipe 'between | quotes' | and out"