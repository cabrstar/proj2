/* Robert Berkley berkob
*  Carter Starr cabrstar
*
*/

#include "recursive.h"
#include <iostream>
#include <cassert>
#include "p2.h"
#include "Recursive_list.h"
#include "Binary_tree.h"
#include "test_helpers.h"

using namespace std;

/* EFFECTS: computes first + n, where first is the first element of
*  the list, and n is the current total.
*/
static int sum_helper(list_t list, int n)
{
	if(list_isEmpty(list))
	{
		return n;
	}
	else
	{
		int first = list_first(list);
		list_t rest = list_rest(list);
		return sum_helper(rest, first + n);
	}
} // end helper function

int sum(list_t list)
{
	int total = sum_helper(list, 0);
	return total;
} //end of function sum

/* EFFECTS: computes first * n, where first is the first element of the
*  list and n is the current product of the list.
*/
static int product_helper(list_t list, int n)
{
	if(list_isEmpty(list))
	{
		return n;
	}
	else
	{
		int first = list_first(list);
		list_t rest = list_rest(list);
		return product_helper(rest, first * n);
	}
} // end helper function

int product(list_t list)
{
	int prod = product_helper(list, 1);
	return prod;
} //end of function product

int accumulate(list_t list, int (*fn)(int, int), int identity)
{
	if(list_isEmpty(list)) // base case
	{
		return identity;
	}
	else // else perform the operation
	{
		int first = list_first(list);
		list = list_rest(list);
		// operation is performed and tracked through calling the function
		// on identity and first when calling the accumulate function
		// recursively.
		return accumulate(list, *fn, fn(identity, first));
	}
}

/* EFFECTS: Takes the first element of list and puts it as the current
*  first element of reversed. As reversed gets built, it becomes the
*  reverse of list.
*/ 
static list_t reverse_helper(list_t list, list_t reversed)
{
	if(list_isEmpty(list))
	{
		return reversed;
	}

	else
	{
		int firstel = list_first(list); //firstel = first element
		list = list_rest(list); // detatching first element off list
		reversed = list_make(firstel, reversed); // place firstel in reversed
		return reverse_helper(list, reversed); // tail recursive call
	}
} // end helper function

list_t reverse(list_t list)
{
	list_t reversed = list_make();
	reversed = reverse_helper(list, reversed);
	return reversed;
} // end function reverse()


/* REQUIRES: first list to be reversed correctly.
*  EFFECTS: adds the last element of first to the beginning of second until
*  list is fully appended.
*/
static list_t append_helper(list_t firstRev, list_t second)
{
	if(list_isEmpty(firstRev)) // base case
	{
		return second;
	}
	// Else list is not empty, take first element (l) from firstRev and
	// put it onto the partially appended list (second).
	else 
	{
		int l = list_first(firstRev);
		firstRev = list_rest(firstRev);
		second = list_make(l, second);
		return append_helper(firstRev, second);
	}
} // end helper function

list_t append(list_t first, list_t second)
{
	first = reverse(first); // reverse now to maintain order
	list_t appended = list_make();
	appended = append_helper(first, second);
	return appended;
} // end function append()


/* EFFECTS: receives an empty list, odds, and stores all odd elements in
*  odds, then returns odds. Receives original list (rest) and deconstructs
*  it, adding the odd elements to odds, removing the rest.
*/
list_t odd_helper(list_t rest, list_t odds)
{
	if(list_isEmpty(rest))
	{
		return odds; // base case
	}
	else
	{
		int first = list_first(rest);
		rest = list_rest(rest);
		if(first % 2 == 1) // number was odd, add to odd list
		{
			odds = list_make(first, odds);
			return odd_helper(rest, odds);
		}
		else // number was even, do not need to add to list
		{
			return odd_helper(rest, odds);
		}
	}
} // end helper function

list_t filter_odd(list_t list)
{
	list = reverse(list); // reverse now to maintain order
	list_t odds = list_make(); // empty list, will store odds
	odds = odd_helper(list, odds);
	return odds;
} // end function filter_odd()


/* EFFECTS: receives an empty list, evens, and stores all even elements in
*  evens, then returns evens. Receives original list (rest) and deconstructs
*  it, adding the even elements to evens, removing the rest.
*/
static list_t even_helper(list_t rest, list_t evens)
{
	if(list_isEmpty(rest))
	{
		return evens; // base case
	}
	else
	{
		int first = list_first(rest);
		rest = list_rest(rest);
		if(first % 2 == 0) // number was even, add to evens list
		{
			evens = list_make(first, evens);
			return even_helper(rest, evens);
		}
		else // number was odd, do not need to add to list
		{
			return even_helper(rest, evens);
		}
	}
}

list_t filter_even(list_t list)
{
	list = reverse(list); // reverse now to maintain order
	list_t evens = list_make(); // empty list, will store evens
	evens = even_helper(list, evens);
	return evens;
}


/* EFFECTS: takes the list, the list of filtered numbers, and a function
*  as input. Then applies the function as a filter, and adds all "caught"
*  numbers to the list of filtered numbers. Reduces list size by one.
*/

static list_t filter_helper(list_t rest, list_t filtered, bool (*fn)(int))
{
	if(list_isEmpty(rest))
	{
		return filtered; // base case
	}
	else
	{
		int first = list_first(rest);
		rest = list_rest(rest);
		if(fn(first) == 1) // number is caught by filter, add to filtered
		{
			filtered = list_make(first, filtered);
			return filter_helper(rest, filtered, *fn);
		}
		else // number is not caught by filter
		{
			return filter_helper(rest, filtered, *fn);
		}
	}
}

list_t filter(list_t list, bool (*fn)(int))
{
	list = reverse(list); // reverse now to maintain order
	list_t filtered = list_make();
	filtered = filter_helper(list, filtered, *fn);
	return filtered;
}

/* EFFECTS: receives the original list, an empty temporary list, and
*  the integer n. Takes the first element of original, stores it in
*  tempList, then appends original to the templist n number of times.
*/

static list_t rotate_helper(list_t original, list_t tempList, int n)
{
	if(n == 0) // base case
	{
		return original;
	}
	else
	{
	int elt = list_first(original); // getting first element
	tempList = list_make(); // clears tempList
	tempList = list_make(elt, tempList); //putting elt in tempList
	original = list_rest(original);
	original = append(original, tempList);
	n--; // decrement n
	return rotate_helper(original, tempList, n); // tail-recursive step
	}
}

list_t rotate(list_t list, int n)
{
	list_t rotated = list_make();
	rotated = rotate_helper(list, rotated, n);
	return rotated;
}

/* EFFECTS: takes list, an empty list, listN, and n. It stores
*  the first n elements of list into listN (backward).
*/

static list_t insert_helper(list_t list, list_t listN, int n)
{
	if(n == 0)
	{
		return listN;
	}
	else
	{
		int elt = list_first(list);
		listN = list_make(elt, listN);
		list = list_rest(list);
		n = n - 1;
		return insert_helper(list, listN, n);
	}
}

list_t insert_list(list_t list, list_t second, int n)
{
	// final is the second chunk of "list", which will come
	// after "second". Created by reversing "list", then chopping
	// the last n elements off, and reversing again.
	list_t final = reverse(list);
	final = chop(final, n);
	final = reverse(final);
	final = append(second, final);

	// listN will be the first n elements of list, followed by second.
	// created using helper function then appending second.
	list_t listN = list_make();
	listN = insert_helper(list, listN, n);
	listN = reverse(listN); // listN is backward

	// appending listN and final to create the desired list.
	final = append(listN, final);
	return final;
}

/* EFFECTS: receives a reversed original list. Takes list_rest
*  of itself n times to give a reversed desired list.
*/

static list_t chopped_helper(list_t chopped, int n)
{
	if(n == 0) // base case
	{
		return chopped;
	}
	else
	{
		chopped = list_rest(chopped);
		return chopped_helper(chopped, n - 1);
	}
}

list_t chop(list_t list, int n)
{
	list = reverse(list); // reversing so list_rest works properly
	list = chopped_helper(list, n);
	list = reverse(list); // reversing again to maintain order
	return list;
}

int fib(int n)
{
	if(n == 0) // first base case.
	{
		return 0;
	}
	else if(n == 1) // second base case
	{
		return 1;
	}
	else
	{
		return fib(n - 1) + fib(n -2); // recursive formula
	}
}

/* EFFECTS: receives initialized sum (1), prev_sum (0), j (1), and n.
*  sum is the current fibonacci number. prev_sum is the fib of (j - 1). 
*  j is our counter, which is counting toward n.
*/

static int fib_tail_helper(int sum, int prev_sum, int j, int n)
{
	if(j == n) // base case.
	{
		return sum;
	}
	else
	{
		j = j + 1; // increment toward n
		return fib_tail_helper(sum + prev_sum, sum, j, n);
	}
}

int fib_tail(int n)
{
	if(n == 0) // "base case"
	{
		return 0;
	}
	else if(n == 1) // "base case 2"
	{
		return 1;
	}

	// because we know n != 0 | 1, we can initialize j to be 1,
	// sum to be 1, and prev_sum to be 0.
	else
	{
		int j = 1;
		int sum = 1;
		int prev_sum = 0;
		int fib_sum = fib_tail_helper(sum, prev_sum, j, n);
		return fib_sum;
	}
}

/*int tree_helper(tree_t treeL, tree_t treeR, int sum) {
*	if (tree_isEmpty(treeL)) {
*		sum += 0;
*	}
*	else {
*		tree_print(treeL);
*		sum += tree_elt(treeL);
*		treeL = tree_left(treeL);
*		tree_t treeRi = tree_right(treeL);
*		sum += tree_helper(treeL, treeRi, 0);
*	}
*	if (tree_isEmpty(treeR)) {
*		sum += 0;
*	}
*	else {
*		tree_print(treeR);
*		sum += tree_elt(treeR);
*		tree_t treeLe = tree_left(treeR);
*		treeR = tree_right(treeR);
*		sum += tree_helper(treeLe, treeR, 0);
*	}
*	return sum;
*}
*
*int tree_sum(tree_t tree) {
*	int sum = 0;
*	if (tree_isEmpty(tree)) {
*	return 0;
*	}
*	else {
*	sum += tree_elt(tree);
*	}
*	tree_t treeL = tree_left(tree);
*	tree_t treeR = tree_right(tree);
*	sum = sum + tree_helper(treeL, treeR, sum);
*	return sum;
}*/

int tree_sum(tree_t tree)
{
	int sum = 0;
	if(tree_isEmpty(tree))
	{
		return 0;
	}
	sum = tree_elt(tree);
	tree_t treeL = tree_left(tree);
	tree_t treeR = tree_right(tree);
	sum += tree_sum(treeL);
	sum += tree_sum(treeR);
	return sum;
}

/* EFFECTS: receives a tree and a list. Goes through the right side
*  and prints to the list.
*/
static list_t traversal_h(tree_t tree, list_t list)
{
	// de-compose tree
	tree_t treeL = tree_left(tree);
	tree_t treeR = tree_right(tree);

	// if the right side's not empty, recurse
	if(!tree_isEmpty(treeR))
	{
		list = traversal_h(treeR, list);
	}
	// put the top element in the list
	int elt = tree_elt(tree);
	list = list_make(elt, list);
	// if the left side's not empty, recurse
	if(!tree_isEmpty(treeL))
	{
		list = traversal_h(treeL, list);
	}

	return list;
} // end helper function

list_t traversal(tree_t tree)
{
	list_t list = list_make();
	list = traversal_h(tree, list);
	return list;
}

bool covered_by(tree_t A, tree_t B)
{
	//base-case 1: tree A is empty. Can return true, as empty trees
	// are covered by all other trees.
	if(tree_isEmpty(A))
	{
		return true;
	}
	//base-case 2: tree B is empty. Can return false because we know
	// A is not empty, and empty trees only cover other empty trees.
	if(tree_isEmpty(B))
	{
		return false;
	}
	//special case: they are equal. They cover each other.
	if(tree_equal(A, B))
	{
		return true;
	}
	//A is covered by B if the elements are equal, A's
	//left subtree is covered by B's left and the 
	// right subtree is covered by B's right.
	else if(tree_elt(A) == tree_elt(B))
	{
		tree_t A_left = tree_left(A);
		tree_t A_right = tree_right(A);
		tree_t B_right = tree_right(B);
		tree_t B_left = tree_left(B);
		return covered_by(A_left, B_left) && covered_by(A_right, B_right);
	}
	// if none of this is met, then A is not covered by B.
	else
	{
		return false;
	}
}

bool contained_by(tree_t A, tree_t B)
{
	// special case: A is covered by B. This means A is contained within B.
	if(covered_by(A, B))
	{
		return true;
	}
	else if(tree_isEmpty(B))
	{
		return false;
	}
	// if the first elements of A and B are equivalent but A is not covered
	// by B, then it cannot be contained by B either.
	else if(tree_elt(A) == tree_elt(B))
	{
		return false;
	}
	else
	{
		tree_t B_left = tree_left(B);
		tree_t B_right = tree_right(B);
		// recursive call
		return contained_by(A, B_left) || contained_by(A, B_right);
	}

}

tree_t insert_tree(int elt, tree_t tree)
{
	if(tree_isEmpty(tree)) // base case
	{
		return tree_make(elt, tree_make(), tree_make());
	}
	// if the element to be inserted is less than the current top element
	// of the tree, then move left.
	if(elt < tree_elt(tree)) 
	{
		tree_t treeL = tree_left(tree); //de-compose left tree
		treeL = insert_tree(elt, treeL); //recursive with left
		tree_t treeR = tree_right(tree); //de-compose right tree
		//put it back together
		tree = tree_make(tree_elt(tree), treeL, treeR);
	}
	// if the element to be inserted is greater than the current top
	// element, then move right
	else
	{
		tree_t treeR = tree_right(tree); //de-compose right tree
		treeR = insert_tree(elt, treeR); //recursive call with right
		tree_t treeL = tree_left(tree); //de-compose left tree
		//put it back together
		tree = tree_make(tree_elt(tree), treeL, treeR);
	}
	return tree; 
}
