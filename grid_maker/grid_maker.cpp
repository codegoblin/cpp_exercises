#include <iostream>
#include <string>

using namespace std;

/*
 * grid_maker.cpp
 *
 * TAKES 2 NUMBERS AND MAKES A GRID composed of 5x3
 * BOXES OUT OF IT, OY.
 *
 * This is a slightly more complex answer to Exercise 8-1 in the book Practical C++ Programming
 * by Steve Oualline
 *
 *  Created on: Feb 25, 2011
 *      Author: Cody Johnston
 */

int main ( )
{
	int grid_width;
	int grid_height;

	int BOX_HEIGHT( 3 );

	cout << "Enter grid width: ";
	cin >> grid_width;
	cout << "Enter grid height: ";
	cin >> grid_height;
	cout << "OK, HERE'S YOUR GRIIIIIIID:\n\n\n";

	for( int h = 0; h < grid_height; h++ )
	{
		for( int bh = 0; bh <= BOX_HEIGHT; bh++ )
		{
			for( int w = 0; w < grid_width; w++ )
			{
				if( bh == 0 )
				{
					cout << "+-----";
				}
				else
				{
					cout << "|     ";
				}
			}

			if ( bh == 0 )
			{
				cout << "+\n";
			}
			else
			{
				cout << "|\n";
			}
		}
	}

	for( int w = 0; w < grid_width; w++ )
	{
		cout << "+-----";
	}

	cout << "+\n";

	return ( 0 );
}

