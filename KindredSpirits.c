// Aadil Habibi
//COP 3502
//aa466902

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

//Setting up prototype functions
void PreOrder(node *root, int *p, int *preArray);
void PostOrder(node *root, int *x, int *postArray);
int SizeCheck(node *root);
int OrderCheck(node *a, node *b);

int isReflection(node *a, node *b)
{
		if (a == NULL && b == NULL)
		{
			//They are both NULL and thus the same
			return 1;
		}
		else if ((a == NULL && b != NULL) || (a != NULL && b == NULL))
		{
			//Only one of them is NULL so they cannot be reflections
			return 0;
		}

		return (a->data == b->data && isReflection(a->left, b->right) && isReflection(a->right, b->left));
}

node *makeReflection(node *root)
{
	if (root == NULL)
		return NULL;

	else
	{
		//Creating space for the reflection
		node *reflect = malloc(sizeof(node));

		//Making data point to the other side to reflect
		reflect->data = root->data;
		reflect->left = makeReflection(root->right);
		reflect->right = makeReflection(root->left);

		return reflect;
	}
}

void PreOrder(node *root, int *p, int *preArray)
{
		if (root == NULL)
			return;

		//Passing in both left and right branches to check Pre Order
		preArray[(*p)++] = root->data;
		PreOrder(root->left, p, preArray);
		PreOrder(root->right, p, preArray);
}

void PostOrder(node *root, int *x, int *postArray)
{
		if (root == NULL)
			return;

		//Passing in both left and right branches to check the Post Order
		PostOrder(root->left, x, postArray);
		PostOrder(root->right, x, postArray);
		postArray[(*x)++] = root->data;
}

int SizeCheck(node *root)
{
		if (root == NULL)
			return 0;

		//Checking the size of the overall tree
		else
			return(SizeCheck(root->left) + 1 + SizeCheck(root->right));
}

//If root1 and 2 are swapped in main, this function will find out
int OrderCheck(node *a, node *b)
{
		int pre1 = a->data;
		int pre2 = -1;
		int post1 = b->data;
		int post2 = -1;
		int ans = 0;

		if(a == NULL || b == NULL)
			return ans;

		//Checking while one side does not equal NULL
		while(a->left != NULL)
		{
			pre2 = a->left->data;
			a = a->left;
		}
		//Checking while other side does not equal NULL
		while (b->right != NULL)
		{
			post2 = b->right->data;
			b = b->right;
		}

		if (pre1 == post2 && pre2 == post1)
			return ans+1;

		return ans;
}

int kindredSpirits(node *a, node *b)
{
		int val = 0;
		int i;
		int count = 0;
		int *p = &count;
		int Bcount = 0;
		int *x = &Bcount;
		int sizea, sizeb, order;

		if(a == NULL && b == NULL)
			return val+1;
		else if ((a == NULL && b != NULL) || (a != NULL && b == NULL))
		{
			return val;
		}

		//Checking for both sizes
		sizea = SizeCheck(a);
		sizeb = SizeCheck(b);

		order = OrderCheck(a, b);

		//Checking if both sides are the same size
		if (sizea != sizeb)
			return val;

		//Creating space for both sides
		int *array1 = malloc(sizeof(int) * sizea);
		int *array2 = malloc(sizeof(int) * sizeb);

		if (order == 1)
		{
			PostOrder(a, x, array2);
			PreOrder(b, p, array1);
		}
		else
		{
			PostOrder(b, x, array2);
			PreOrder(a, p, array1);
		}

		//Checking to see if the indexes of both arrays are equal
		//if not then exit
		for(i = 0; i < sizea; i++)
		{
			if(array1[i]!= array2[i])
			return val;
		}

		return val+1;
}

double difficultyRating(void)
{
	return 3;
}

double hoursSpent(void)
{
	return 15;
}
