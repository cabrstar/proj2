#include "p2.h"
#include "recursive.h"
#include  "test_helpers.h"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

// YOU MUST EXTEND THE MAIN FUNCTION IN THIS FILE SO THAT IT TESTS EVERY
// PUBLIC FUNCTION YOU IMPLEMENT IN P2.CPP!
//
// Protip #1: Write tests for the functions BEFORE you implement them!
// (i.e. Write tests for sum() first, and then write sum())
// It sounds like a pain, but it helps make sure that you are never under the
// illusion that your code works when it's actually full of bugs.
//
// Protip #2: Instead of putting all your tests in main() (and making life
// more difficult--especially for the graders), put each test case in a
// function!
//
//
// We recommend using the functions in test_helpers.h when
// writing your test cases.
//

void test_sum_basic();
// basic list created.

void test_sum_empty();
// testing on an empty list

void test_sum_complex();
// testing on a bigger, more complex list

void test_prod_basic();
// testing on a basic list (same method as sum_basic)

void test_prod_empty();
// testing on an empty list

void test_prod_complex();
// testing on a bigger, more complex list (same method as
// sum_complex, but without zeros)

void test_prod_zeros();
// testing on a smaller list that has the possibility of zeros

void test_reverse_basic();
// testing on a hard-coded, basic list

void test_odds();
// testing a hard-coded, basic list

void test_evens();
// testing a hard-coded, basic list

void test_append();

void test_rotate();

void test_chop();
// testing a hard-coded, basic list

void test_insert();

void test_fib();

void test_fib_tail();

void test_tree_sum();

void test_tree_traversal();

int add();

void test_accumulate();

int multiply();

void test_contained_by();

void insert_test();

bool is_multiple_three();

void filter_test();

//void test_covered_by();


int main()
{
    test_sum_basic();
    // ---- Call your test functions here ----
    test_sum_empty();
    test_sum_complex();
    test_prod_complex();
    test_prod_basic();
    test_prod_empty();
    test_prod_zeros();
    test_reverse_basic();
    test_odds();
    test_evens();
    test_rotate();
    test_chop();
    test_insert();
    test_fib();
    test_fib_tail();
    test_tree_sum();
    test_tree_traversal();
    test_accumulate();
//    test_covered_by();
    test_contained_by();
    insert_test();
    filter_test();
    test_append();
    return 0;
}

void test_sum_basic()
{
    cout << "Sum Test: Basic" << endl;

    // Here's a free test case! You can model your tests after this one.
    list_t listA = list_make();

    for (int i = 0; i < 5; ++i)
    {
        listA = list_make(i, listA);
    }

    const int EXPECTED_SUM = 10;
    int actual_sum = sum(listA);
    cout << "Expected sum: " << EXPECTED_SUM << endl;
    cout << "Actual sum: " << actual_sum << endl;
    assert(EXPECTED_SUM == actual_sum);

    cout << "PASS!" << endl;
}

// ---- Add your test function implementations here ----

void test_sum_empty()
{
    cout << "Sum Test: Empty List" << endl;

    list_t listA = list_make();

    const int EXPECTED_SUM = 0;
    int actual_sum = sum(listA);
    cout << "Expected sum: " << EXPECTED_SUM << endl;
    cout << "Actual sum: " << actual_sum << endl;
    assert(EXPECTED_SUM == actual_sum);

    cout << "PASS!" << endl;
}

void test_sum_complex()
{
    cout << "Sum Test: Complex" << endl;

    list_t listA = list_make();

    // initialize variables before loop
    int expected_sum = 0;
    int random = 0;

    // create random seed    
    srand (time(NULL));

    // Generating a list of 100 elements of random numbers between
    // 0 and 99. Keeping track of expected_sum as the list is formed.
    for(int i = 0; i < 100; i++)
    {
        random = rand() % 101;
        expected_sum = expected_sum + random;
        listA = list_make(random, listA);
    }
    int actual_sum = sum(listA);
    cout << "Expected sum: " << expected_sum << endl;
    cout << "Actual sum: " << actual_sum << endl;
    assert(expected_sum == actual_sum);

    cout << "PASS!" << endl;
}

void test_prod_complex()
{
    cout << "Product test: Complex (no zeros)" << endl;
    list_t listA = list_make();

    // initialize variables before loop
    int expected_prod = 1;
    int random = 0;

    // create random seed
    srand (time(NULL));

    // Generating a list of 10 elements of random numbers between
    // 1 and 10. Keeping track of expected_prod as the list is formed.
    for(int i = 0; i < 10; i++)
    {
        random = rand() % 10 + 1;
        expected_prod = expected_prod * random;
        listA = list_make(random, listA);
    }

    int actual_prod = product(listA);
    cout << "Expected product: " << expected_prod << endl;
    cout << "Actual product: " << actual_prod << endl;
    assert(expected_prod == actual_prod);

    cout << "PASS!" << endl;
}

void test_prod_basic()
{
    cout << "Product test: Basic" << endl;

    list_t listA = list_make();
    for(int i = 1; i < 6; i++)
    {
        listA = list_make(i, listA);
    }
    const int EXPECTED_PROD = 120;
    int actual_prod = product(listA);
    cout << "Expected product: " << EXPECTED_PROD << endl;
    cout << "Actual product: " << actual_prod << endl;
    assert(EXPECTED_PROD == actual_prod);

    cout << "PASS!" << endl;
}

void test_prod_empty()
{
    cout << "Product test: empty" << endl;

    list_t listA = list_make();

    const int EXPECTED_PROD = 1;
    int actual_prod = product(listA);

    cout << "Expected product: " << EXPECTED_PROD << endl;
    cout << "Actual product: " << actual_prod << endl;
    assert(EXPECTED_PROD == actual_prod);

    cout << "PASS!" << endl;
}

void test_prod_zeros()
{
    cout << "Product test: zeros" << endl;

    list_t listA = list_make();

    // initialize variables before loop
    int expected_prod = 1;
    int random = 0;

    //create random seed
    srand (time(NULL));

    // Generating a list of 5 elements between 0 and 10. 0s are not
    // to be expected, but are a possibility that repeated use of this
    // test can account for.
    for(int i = 0; i < 5; i++)
    {
        random = rand() % 11;
        expected_prod = expected_prod * random;
        listA = list_make(random, listA);
    }

    int actual_prod = product(listA);
    cout << "Expected product: " << expected_prod << endl;
    cout << "Actual product: " << actual_prod << endl;
    assert(expected_prod == actual_prod);

    cout << "PASS!" << endl;
}

void test_reverse_basic()
{
    cout << "Reverse test: basic" << endl;

    list_t listA = list_make();
    for(int i = 0; i < 5; i++)
    {
        listA = list_make(i, listA);
    }
    list_t listB = list_make();
    for(int j = 4; j > -1; j--)
    {
        listB = list_make(j, listB);
    }
    listA = reverse(listA);

    list_t list_test = listA;

    /*for(int k = 0; k < 5; k++)
    *{
    *    int elt = list_first(list_test);
    *    list_test = list_rest(list_test);
    *    cout << elt << " ";
    *}
    *cout << endl;
    *
    *for(int l = 0; l < 5; l++)
    *{
    *    int elt = list_first(listB);
    *    listB = list_rest(listB);
    *    cout << elt << " ";
    *}
    (cout << endl;
        */
    assert(list_equal(listA, listB));
    cout << "PASS!" << endl;
}

void test_odds()
{
    cout << "Odds test" << endl;
    list_t listA = list_make();

    for (int i = 0; i < 5; ++i)
    {
        listA = list_make(i, listA);
    }

    list_t listNew = list_make();
    listNew = list_make(1, listNew);
    listNew = list_make(3, listNew);
    list_t actualList = list_make();
    actualList = filter_odd(listA);
    
    assert(list_equal(listNew, actualList));

    cout << "Pass!" << endl;
}

void test_evens()
{
    cout << "Evens test" << endl;
    list_t listA = list_make();

    for (int i = 0; i < 5; ++i)
    {
        listA = list_make(i, listA);
    }

    list_t listNew = list_make();
    listNew = list_make(0, listNew);
    listNew = list_make(2, listNew);
    listNew = list_make(4, listNew);
    list_t actualList = list_make();
    actualList = filter_even(listA);
    
    assert(list_equal(listNew, actualList));

    cout << "Pass!" << endl;
}

void test_append()
{
    cout << "Appendectime" << endl;
    list_t listA = list_make();
    for (int i = 0; i < 5; i++)
    {
        listA = list_make(i, listA);
    }
    list_t listB = list_make();
    for (int j = 5; j < 10; j++)
    {
        listB = list_make(j, listB);
    }
    list_t list_Correct = list_make();
    for (int k = 0; k < 10; k++)
    {
        list_Correct = list_make(k, list_Correct);
    }
    listB = append(listB, listA);
    assert(list_equal(listB, list_Correct));
    cout << "You can dePEND on apPEND!!!!!`1!#$143134 ROFLmaooooooooooooooooooo" << endl;
}

void test_rotate()
{
    cout << "Rotate test: " << endl;
    list_t listA = list_make();

    for(int i = 0; i < 5; i++)
    {
        listA = list_make(i, listA);
    }
    list_t listNew = listA;
    listA = rotate(listA, 5);
    assert(list_equal(listNew, listA));
    cout << "Pass!" << endl;
}

void test_chop()
{
    cout << "Chop test: " << endl;
    list_t list = list_make();
    for(int i = 4; i > -1; i--)
    {
        list = list_make(i, list);
    }
    list_t listNew = list_make();
    for(int j = 2; j > -1; j--)
    {
        listNew = list_make(j, listNew);
    }
    list = chop(list, 2);
    //list_print(listNew);
    //list_print(list);
    assert(list_equal(listNew, list));
    cout << "Pass!" << endl;
}

// TEST NOT COMPLETE;ALDSFKJ;ALSDKFJ;ADSLKFJ;LASDKFJA;SDLKFJAS;DLFKJA;SDLK
void test_insert()
{
    cout << "Insert test: " << endl;
    list_t first = list_make();
    for(int i = 3; i > 0; i--)
    {
        first = list_make(i, first);
    }
    list_t second = list_make();
    for(int j = 6; j > 3; j--)
    {
        second = list_make(j, second);
    }
    list_t final = insert_list(first, second, 2);
    list_print(final);
    cout << "Pass!" << endl;
}

void test_fib()
{
    cout << "Fib test" << endl;
    assert(fib(5) == 5);
    assert(fib(0) == 0);
    assert(fib(1) == 1);
    assert(fib(8) == 21);
    assert(fib(10) == 55);
    assert(fib(20) == 6765);
    cout << "PASS DAWG" << endl;
}

void test_fib_tail()
{
    cout << "Fib test: tail" << endl;
    assert(fib_tail(5) == 5);
    assert(fib_tail(0) == 0);
    assert(fib_tail(1) == 1);
    assert(fib_tail(8) == 21);
    assert(fib_tail(10) == 55);
    assert(fib_tail(20) == 6765);
    cout << "PASS DAWG" << endl;
}

void test_tree_sum()
{
    cout << "Tree Sum test" << endl;
    tree_t tree = tree_make();
    tree = tree_make(4, tree, tree);
    tree = tree_make(8, tree, tree);
    tree = tree_make(32, tree, tree);
    int correct_sum = 64;
    int sum = tree_sum(tree);
    assert(correct_sum == sum);
}

void test_tree_traversal()
{
    cout << "Tree traversal test:" << endl;
    tree_t tree_empty = tree_make();
    tree_t tree_3 = tree_make();
    tree_3 = tree_make(3, tree_empty, tree_empty);
    tree_t tree_2 = tree_make(2, tree_empty, tree_3);
    tree_t tree_5 = tree_make(5, tree_empty, tree_empty);
    tree_t tree_4 = tree_make(4, tree_2, tree_5);
    tree_print(tree_4);
    list_t list = list_make();
    list = list_make(5, list);
    list = list_make(4, list);
    list = list_make(3, list);
    list = list_make(2, list);
    list_t list_test = traversal(tree_4);
    list_print(list);
    list_print(list_test);
    assert(list_equal(list_test, list));
}

int add(int x, int y)
{
    return (x + y);
}

int multiply(int x, int y)
{
    return (x * y);
}

void test_accumulate()
{
    cout << "Accumulate test: addition" << endl;
    list_t list = list_make();
    for(int i = 1; i < 6; i++)
    {
        list = list_make(i, list);
    }
    int addition = accumulate(list, add, 0);
    int multiplication = accumulate(list, multiply, 1);
    int correct_addition = 15;
    int correct_multiplication = 120;
    assert(addition == correct_addition);
    cout << "PASS!" << endl;
    cout << "Accumulate test: multiplication:" << endl;
    assert(multiplication == correct_multiplication);
    cout << "PASSSSSSSSSSSSS!!!!!1!" << endl;
}

/*void test_covered_by()
{
    cout << "Covered by test" << endl;
    tree_t tree_empty = tree_make();
    tree_t tree_3 = tree_make();
    tree_3 = tree_make(3, tree_empty, tree_empty);
    tree_t tree_2 = tree_make(2, tree_empty, tree_3);
    tree_t tree_5 = tree_make(5, tree_empty, tree_empty);
    tree_t tree_4 = tree_make(4, tree_2, tree_5);
    tree_print(tree_4);
    tree_t small = tree_make();
    small = tree_make(2, tree_empty, tree_empty);
    small = tree_make(4, small, tree_empty);
    tree_print(small);
    tree_t wrong = tree_make(4, tree_3, tree_empty);
    assert( covered_by(small, tree_4));
    assert( !covered_by(tree_5, tree_4));
    cout << "PASS!" << endl;
}*/

void test_contained_by()
{
    cout << "Contained by test" << endl;
    tree_t tree_empty = tree_make();
    tree_t tree_3 = tree_make();
    tree_3 = tree_make(3, tree_empty, tree_empty);
    tree_t tree_2 = tree_make(2, tree_empty, tree_3);
    tree_t tree_5 = tree_make(5, tree_empty, tree_empty);
    tree_t tree_4 = tree_make(4, tree_2, tree_5);
    tree_print(tree_4);
    tree_t small = tree_make();
    small = tree_make(2, small, small);
    tree_t wrong = tree_make(4, tree_3, tree_empty);
    assert(contained_by(small, tree_4));
    cout << "Pass 1" << endl;
    assert(contained_by(tree_empty, tree_4));
    cout << "Pass 2" << endl;
    assert(contained_by(tree_4, tree_4));
    cout << "Pass 3" << endl;
    assert(!contained_by(wrong, tree_4));
    cout << "Pass 4" << endl;
    assert(contained_by(tree_5, tree_4));
    cout << "Pass 5" << endl;
    assert(contained_by(tree_3, tree_4));
    cout << "Pass ALL" << endl;

}

void insert_test()
{
    cout << "Insert tree test: " << endl;
    tree_t tree_empty = tree_make();
    tree_t tree_3 = tree_make();
    tree_3 = tree_make(3, tree_empty, tree_empty);
    tree_t tree_2 = tree_make(2, tree_empty, tree_3);
    tree_t tree_5 = tree_make(5, tree_empty, tree_empty);
    tree_t tree_4 = tree_make(4, tree_2, tree_5);
    tree_4 = insert_tree(3, tree_4);
    tree_t emptytest = insert_tree(3, tree_empty);
    tree_print(emptytest);
    tree_print(tree_4);
    assert(tree_equal(emptytest, tree_3));
    cout << "empty test passed!" << endl;
    tree_3 = tree_make(3, tree_empty, tree_3);
    tree_2 = tree_make(2, tree_empty, tree_3);
    tree_t correct = tree_make(4, tree_2, tree_5);
    assert(tree_equal(tree_4, correct));
    cout << "primary test passed!" << endl;
}

bool is_multiple_three(int x)
{
    if(x % 3 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void filter_test()
{
    cout << "filter test" << endl;
    list_t list = list_make();
    for(int i = 0; i < 16; i++)
    {
        list = list_make(i, list);
    }
    list_t correct = list_make();
    for(int j = 0; j < 16; j += 3)
    {
        correct = list_make(j, correct);
    }
    list = filter(list, is_multiple_three);
    assert(list_equal(list, correct));
    cout << "PASS" << endl;
}








