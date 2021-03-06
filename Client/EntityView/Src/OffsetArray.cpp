//==========================================================================
/**
* @file	  : OffsetArray.cpp
* @author : 
* created : 2008-2-16   12:45
*/
//==========================================================================

#include "stdafx.h"
#include "OffsetArray.h"

enum {Cricle3_Size=37, Cricle4_Size=69, Cricle5_Size=97, Cricle6_Size=129,
Cricle7_Size=165, Cricle8_Size=205, Cricle9_Size=249,
Cricle10_Size=329, Cricle11_Size=385, Cricle12_Size=445};

/// 半径为3的圆形
const TileOffset arrOffsetCircle3[Cricle3_Size] = 
{
					{-1, 3},{ 0, 3},{ 1, 3},
			{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},
	{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},
	{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},
	{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},
			{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},
					{-1,-3},{ 0,-3},{ 1,-3},
};


/// 半径为4的圆形
const TileOffset arrOffsetCircle4[Cricle4_Size] = 
{
					{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},
			{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},
	{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},
	{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},
	{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},
	{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},
	{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},
			{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},
					{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4}
};

/// 半径为5的圆形
const TileOffset arrOffsetCircle5[Cricle5_Size] = 
{
						{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},
				{-3, 4},{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},{ 3, 4},
		{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},
{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},
{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},
{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},
{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},
{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},
		{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},
				{-3,-4},{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},{ 3,-4},
						{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5}
};

/// 半径为6的圆形
const TileOffset arrOffsetCircle6[Cricle6_Size] = 
{
								{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},
						{-3, 5},{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},{ 3, 5},
				{-4, 4},{-3, 4},{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},
		{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},
{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},
{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},
{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},
{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},
{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},
		{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},
				{-4,-4},{-3,-4},{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},
						{-3,-5},{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},{ 3,-5},
								{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6}
};

/// 半径为7的圆形
const TileOffset arrOffsetCircle7[Cricle7_Size] = 
{
										{-2, 7},{-1, 7},{ 0, 7},{ 1, 7},{ 2, 7},
								{-3, 6},{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},{ 3, 6},
						{-4, 5},{-3, 5},{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},{ 3, 5},{ 4, 5},
				{-5, 4},{-4, 4},{-3, 4},{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},{ 5, 4},
		{-6, 3},{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},{ 6, 3},
{-7, 2},{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},{ 7, 2},
{-7, 1},{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},{ 7, 1},
{-7, 0},{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},{ 7, 0},
{-7,-1},{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},{ 7,-1},
{-7,-2},{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},{ 7,-2},
		{-6,-3},{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},{ 6,-3},
				{-5,-4},{-4,-4},{-3,-4},{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},{ 5,-4},
						{-4,-5},{-3,-5},{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},{ 3,-5},{ 4,-5},
								{-3,-6},{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6},{ 3,-6},
										{-2,-7},{-1,-7},{ 0,-7},{ 1,-7},{ 2,-7}
};

/// 半径为8的圆形
const TileOffset arrOffsetCircle8[Cricle8_Size] = 
{
												{-2, 8},{-1, 8},{ 0, 8},{ 1, 8},{ 2, 8},
										{-3, 7},{-2, 7},{-1, 7},{ 0, 7},{ 1, 7},{ 2, 7},{ 3, 7},
								{-4, 6},{-3, 6},{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},{ 3, 6},{ 4, 6},
						{-5, 5},{-4, 5},{-3, 5},{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},{ 3, 5},{ 4, 5},{ 5, 5},
				{-6, 4},{-5, 4},{-4, 4},{-3, 4},{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},{ 5, 4},{ 6, 4},
		{-7, 3},{-6, 3},{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},{ 6, 3},{ 7, 3},
{-8, 2},{-7, 2},{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},{ 7, 2},{ 8, 2},
{-8, 1},{-7, 1},{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},{ 7, 1},{ 8, 1},
{-8, 0},{-7, 0},{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},{ 7, 0},{ 8, 0},
{-8,-1},{-7,-1},{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},{ 7,-1},{ 8,-1},
{-8,-2},{-7,-2},{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},{ 7,-2},{ 8,-2},
		{-7,-3},{-6,-3},{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},{ 6,-3},{ 7,-3},
				{-6,-4},{-5,-4},{-4,-4},{-3,-4},{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},{ 5,-4},{ 6,-4},
						{-5,-5},{-4,-5},{-3,-5},{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},{ 3,-5},{ 4,-5},{ 5,-5},
								{-4,-6},{-3,-6},{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6},{ 3,-6},{ 4,-6},
										{-3,-7},{-2,-7},{-1,-7},{ 0,-7},{ 1,-7},{ 2,-7},{ 3,-7},
												{-2,-8},{-1,-8},{ 0,-8},{ 1,-8},{ 2,-8}
};

/// 半径为9的圆形
const TileOffset arrOffsetCircle9[Cricle9_Size] = 
{
														{-2, 9},{-1, 9},{ 0, 9},{ 1, 9},{ 2, 9},
												{-3, 8},{-2, 8},{-1, 8},{ 0, 8},{ 1, 8},{ 2, 8},{ 3, 8},
										{-4, 7},{-3, 7},{-2, 7},{-1, 7},{ 0, 7},{ 1, 7},{ 2, 7},{ 3, 7},{ 4, 7},
								{-5, 6},{-4, 6},{-3, 6},{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},{ 3, 6},{ 4, 6},{ 5, 6},
						{-6, 5},{-5, 5},{-4, 5},{-3, 5},{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},{ 3, 5},{ 4, 5},{ 5, 5},{ 6, 5},
				{-7, 4},{-6, 4},{-5, 4},{-4, 4},{-3, 4},{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},{ 5, 4},{ 6, 4},{ 7, 4},
		{-8, 3},{-7, 3},{-6, 3},{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},{ 6, 3},{ 7, 3},{ 8, 3},
{-9, 2},{-8, 2},{-7, 2},{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},{ 7, 2},{ 8, 2},{ 9, 2},
{-9, 1},{-8, 1},{-7, 1},{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},{ 7, 1},{ 8, 1},{ 9, 1},
{-9, 0},{-8, 0},{-7, 0},{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},{ 7, 0},{ 8, 0},{ 9, 0},
{-9,-1},{-8,-1},{-7,-1},{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},{ 7,-1},{ 8,-1},{ 9,-1},
{-9,-2},{-8,-2},{-7,-2},{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},{ 7,-2},{ 8,-2},{ 9,-2},
		{-8,-3},{-7,-3},{-6,-3},{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},{ 6,-3},{ 7,-3},{ 8,-3},
				{-7,-4},{-6,-4},{-5,-4},{-4,-4},{-3,-4},{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},{ 5,-4},{ 6,-4},{ 7,-4},
						{-6,-5},{-5,-5},{-4,-5},{-3,-5},{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},{ 3,-5},{ 4,-5},{ 5,-5},{ 6,-5},
								{-5,-6},{-4,-6},{-3,-6},{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6},{ 3,-6},{ 4,-6},{ 5,-6},
										{-4,-7},{-3,-7},{-2,-7},{-1,-7},{ 0,-7},{ 1,-7},{ 2,-7},{ 3,-7},{ 4,-7},
												{-3,-8},{-2,-8},{-1,-8},{ 0,-8},{ 1,-8},{ 2,-8},{ 3,-8},
														{-2,-9},{-1,-9},{ 0,-9},{ 1,-9},{ 2,-9}
};

/// 半径为10的圆形
const TileOffset arrOffsetCircle10[Cricle10_Size] = 
{
														{-3, 10},{-2, 10},{-1, 10},{ 0, 10},{ 1, 10},{ 2, 10},{ 3, 10},
												{-4, 9},{-3, 9},{-2, 9},{-1, 9},{ 0, 9},{ 1, 9},{ 2, 9},{ 3, 9},{ 4, 9},
										{-5, 8},{-4, 8},{-3, 8},{-2, 8},{-1, 8},{ 0, 8},{ 1, 8},{ 2, 8},{ 3, 8},{ 4, 8},{ 5, 8},
								{-6, 7},{-5, 7},{-4, 7},{-3, 7},{-2, 7},{-1, 7},{ 0, 7},{ 1, 7},{ 2, 7},{ 3, 7},{ 4, 7},{ 5, 7},{ 6, 7},
						{-7, 6},{-6, 6},{-5, 6},{-4, 6},{-3, 6},{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},{ 3, 6},{ 4, 6},{ 5, 6},{ 6, 6},{ 7, 6},
				{-8, 5},{-7, 5},{-6, 5},{-5, 5},{-4, 5},{-3, 5},{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},{ 3, 5},{ 4, 5},{ 5, 5},{ 6, 5},{ 7, 5},{ 8, 5},
		{-9, 4},{-8, 4},{-7, 4},{-6, 4},{-5, 4},{-4, 4},{-3, 4},{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},{ 5, 4},{ 6, 4},{ 7, 4},{ 8, 4},{ 9, 4},
{-10, 3},{-9, 3},{-8, 3},{-7, 3},{-6, 3},{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},{ 6, 3},{ 7, 3},{ 8, 3},{ 9, 3},{ 10, 3},
{-10, 2},{-9, 2},{-8, 2},{-7, 2},{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},{ 7, 2},{ 8, 2},{ 9, 2},{ 10, 2},
{-10, 1},{-9, 1},{-8, 1},{-7, 1},{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},{ 7, 1},{ 8, 1},{ 9, 1},{ 10, 1},
{-10, 0},{-9, 0},{-8, 0},{-7, 0},{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},{ 7, 0},{ 8, 0},{ 9, 0},{ 10, 0},
{-10,-1},{-9,-1},{-8,-1},{-7,-1},{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},{ 7,-1},{ 8,-1},{ 9,-1},{ 10,-1},
{-10,-2},{-9,-2},{-8,-2},{-7,-2},{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},{ 7,-2},{ 8,-2},{ 9,-2},{ 10,-2},
{-10,-3},{-9,-3},{-8,-3},{-7,-3},{-6,-3},{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},{ 6,-3},{ 7,-3},{ 8,-3},{ 9,-3},{ 10,-3},
		{-9,-4},{-8,-4},{-7,-4},{-6,-4},{-5,-4},{-4,-4},{-3,-4},{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},{ 5,-4},{ 6,-4},{ 7,-4},{ 8,-4},{ 9,-4},
				{-8,-5},{-7,-5},{-6,-5},{-5,-5},{-4,-5},{-3,-5},{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},{ 3,-5},{ 4,-5},{ 5,-5},{ 6,-5},{ 7,-5},{ 8,-5},
						{-7,-6},{-6,-6},{-5,-6},{-4,-6},{-3,-6},{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6},{ 3,-6},{ 4,-6},{ 5,-6},{ 6,-6},{ 7,-6},
								{-6,-7},{-5,-7},{-4,-7},{-3,-7},{-2,-7},{-1,-7},{ 0,-7},{ 1,-7},{ 2,-7},{ 3,-7},{ 4,-7},{ 5,-7},{ 6,-7},
										{-5,-8},{-4,-8},{-3,-8},{-2,-8},{-1,-8},{ 0,-8},{ 1,-8},{ 2,-8},{ 3,-8},{ 4,-8},{ 5,-8},
												{-4,-9},{-3,-9},{-2,-9},{-1,-9},{ 0,-9},{ 1,-9},{ 2,-9},{ 3,-9},{ 4,-9},
														{-3,-10},{-2,-10},{-1,-10},{ 0,-10},{ 1,-10},{ 2,-10},{ 3,-10}
};

/// 半径为11的圆形
const TileOffset arrOffsetCircle11[Cricle11_Size] = 
{
																{-3, 11},{-2, 11},{-1, 11},{ 0, 11},{ 1, 11},{ 2, 11},{ 3, 11},
														{-4, 10},{-3, 10},{-2, 10},{-1, 10},{ 0, 10},{ 1, 10},{ 2, 10},{ 3, 10},{ 4, 10},
												{-5, 9},{-4, 9},{-3, 9},{-2, 9},{-1, 9},{ 0, 9},{ 1, 9},{ 2, 9},{ 3, 9},{ 4, 9},{ 5, 9},
										{-6, 8},{-5, 8},{-4, 8},{-3, 8},{-2, 8},{-1, 8},{ 0, 8},{ 1, 8},{ 2, 8},{ 3, 8},{ 4, 8},{ 5, 8},{ 6, 8},
								{-7, 7},{-6, 7},{-5, 7},{-4, 7},{-3, 7},{-2, 7},{-1, 7},{ 0, 7},{ 1, 7},{ 2, 7},{ 3, 7},{ 4, 7},{ 5, 7},{ 6, 7},{ 7, 7},
						{-8, 6},{-7, 6},{-6, 6},{-5, 6},{-4, 6},{-3, 6},{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},{ 3, 6},{ 4, 6},{ 5, 6},{ 6, 6},{ 7, 6},{ 8, 6},
				{-9, 5},{-8, 5},{-7, 5},{-6, 5},{-5, 5},{-4, 5},{-3, 5},{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},{ 3, 5},{ 4, 5},{ 5, 5},{ 6, 5},{ 7, 5},{ 8, 5},{ 9, 5},
		{-10, 4},{-9, 4},{-8, 4},{-7, 4},{-6, 4},{-5, 4},{-4, 4},{-3, 4},{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},{ 5, 4},{ 6, 4},{ 7, 4},{ 8, 4},{ 9, 4},{ 10, 4},
{-11, 3},{-10, 3},{-9, 3},{-8, 3},{-7, 3},{-6, 3},{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},{ 6, 3},{ 7, 3},{ 8, 3},{ 9, 3},{ 10, 3},{ 11, 3},
{-11, 2},{-10, 2},{-9, 2},{-8, 2},{-7, 2},{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},{ 7, 2},{ 8, 2},{ 9, 2},{ 10, 2},{ 11, 2},
{-11, 1},{-10, 1},{-9, 1},{-8, 1},{-7, 1},{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},{ 7, 1},{ 8, 1},{ 9, 1},{ 10, 1},{ 11, 1},
{-11, 0},{-10, 0},{-9, 0},{-8, 0},{-7, 0},{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},{ 7, 0},{ 8, 0},{ 9, 0},{ 10, 0},{ 11, 0},
{-11,-1},{-10,-1},{-9,-1},{-8,-1},{-7,-1},{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},{ 7,-1},{ 8,-1},{ 9,-1},{ 10,-1},{ 11,-1},
{-11,-2},{-10,-2},{-9,-2},{-8,-2},{-7,-2},{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},{ 7,-2},{ 8,-2},{ 9,-2},{ 10,-2},{ 11,-2},
{-11,-3},{-10,-3},{-9,-3},{-8,-3},{-7,-3},{-6,-3},{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},{ 6,-3},{ 7,-3},{ 8,-3},{ 9,-3},{ 10,-3},{ 11,-3},
		{-10,-4},{-9,-4},{-8,-4},{-7,-4},{-6,-4},{-5,-4},{-4,-4},{-3,-4},{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},{ 5,-4},{ 6,-4},{ 7,-4},{ 8,-4},{ 9,-4},{ 10,-4},
				{-9,-5},{-8,-5},{-7,-5},{-6,-5},{-5,-5},{-4,-5},{-3,-5},{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},{ 3,-5},{ 4,-5},{ 5,-5},{ 6,-5},{ 7,-5},{ 8,-5},{ 9,-5},
						{-8,-6},{-7,-6},{-6,-6},{-5,-6},{-4,-6},{-3,-6},{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6},{ 3,-6},{ 4,-6},{ 5,-6},{ 6,-6},{ 7,-6},{ 8,-6},
								{-7,-7},{-6,-7},{-5,-7},{-4,-7},{-3,-7},{-2,-7},{-1,-7},{ 0,-7},{ 1,-7},{ 2,-7},{ 3,-7},{ 4,-7},{ 5,-7},{ 6,-7},{ 7,-7},
										{-6,-8},{-5,-8},{-4,-8},{-3,-8},{-2,-8},{-1,-8},{ 0,-8},{ 1,-8},{ 2,-8},{ 3,-8},{ 4,-8},{ 5,-8},{ 6,-8},
												{-5,-9},{-4,-9},{-3,-9},{-2,-9},{-1,-9},{ 0,-9},{ 1,-9},{ 2,-9},{ 3,-9},{ 4,-9},{ 5,-9},
														{-4,-10},{-3,-10},{-2,-10},{-1,-10},{ 0,-10},{ 1,-10},{ 2,-10},{ 3,-10},{ 4,-10},
																{-3,-11},{-2,-11},{-1,-11},{ 0,-11},{ 1,-11},{ 2,-11},{ 3,-11}
};

/// 半径为12的圆形
const TileOffset arrOffsetCircle12[Cricle12_Size] = 
{
																		{-3, 12},{-2, 12},{-1, 12},{ 0, 12},{ 1, 12},{ 2, 12},{ 3, 12},
																{-4, 11},{-3, 11},{-2, 11},{-1, 11},{ 0, 11},{ 1, 11},{ 2, 11},{ 3, 11},{ 4, 11},
														{-5, 10},{-4, 10},{-3, 10},{-2, 10},{-1, 10},{ 0, 10},{ 1, 10},{ 2, 10},{ 3, 10},{ 4, 10},{ 5, 10},
												{-6, 9},{-5, 9},{-4, 9},{-3, 9},{-2, 9},{-1, 9},{ 0, 9},{ 1, 9},{ 2, 9},{ 3, 9},{ 4, 9},{ 5, 9},{ 6, 9},
										{-7, 8},{-6, 8},{-5, 8},{-4, 8},{-3, 8},{-2, 8},{-1, 8},{ 0, 8},{ 1, 8},{ 2, 8},{ 3, 8},{ 4, 8},{ 5, 8},{ 6, 8},{ 7, 8},
								{-8, 7},{-7, 7},{-6, 7},{-5, 7},{-4, 7},{-3, 7},{-2, 7},{-1, 7},{ 0, 7},{ 1, 7},{ 2, 7},{ 3, 7},{ 4, 7},{ 5, 7},{ 6, 7},{ 7, 7},{ 8, 7},
						{-9, 6},{-8, 6},{-7, 6},{-6, 6},{-5, 6},{-4, 6},{-3, 6},{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},{ 3, 6},{ 4, 6},{ 5, 6},{ 6, 6},{ 7, 6},{ 8, 6},{ 9, 6},
				{-10, 5},{-9, 5},{-8, 5},{-7, 5},{-6, 5},{-5, 5},{-4, 5},{-3, 5},{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},{ 3, 5},{ 4, 5},{ 5, 5},{ 6, 5},{ 7, 5},{ 8, 5},{ 9, 5},{ 10, 5},
		{-11, 4},{-10, 4},{-9, 4},{-8, 4},{-7, 4},{-6, 4},{-5, 4},{-4, 4},{-3, 4},{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},{ 5, 4},{ 6, 4},{ 7, 4},{ 8, 4},{ 9, 4},{ 10, 4},{ 11, 4},
{-12, 3},{-11, 3},{-10, 3},{-9, 3},{-8, 3},{-7, 3},{-6, 3},{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},{ 6, 3},{ 7, 3},{ 8, 3},{ 9, 3},{ 10, 3},{ 11, 3},{ 12, 3},
{-12, 2},{-11, 2},{-10, 2},{-9, 2},{-8, 2},{-7, 2},{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},{ 7, 2},{ 8, 2},{ 9, 2},{ 10, 2},{ 11, 2},{ 12, 2},
{-12, 1},{-11, 1},{-10, 1},{-9, 1},{-8, 1},{-7, 1},{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},{ 7, 1},{ 8, 1},{ 9, 1},{ 10, 1},{ 11, 1},{ 12, 1},
{-12, 0},{-11, 0},{-10, 0},{-9, 0},{-8, 0},{-7, 0},{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},{ 0, 0},{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},{ 7, 0},{ 8, 0},{ 9, 0},{ 10, 0},{ 11, 0},{ 12, 0},
{-12,-1},{-11,-1},{-10,-1},{-9,-1},{-8,-1},{-7,-1},{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},{ 7,-1},{ 8,-1},{ 9,-1},{ 10,-1},{ 11,-1},{ 12,-1},
{-12,-2},{-11,-2},{-10,-2},{-9,-2},{-8,-2},{-7,-2},{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},{ 7,-2},{ 8,-2},{ 9,-2},{ 10,-2},{ 11,-2},{ 12,-2},
{-12,-3},{-11,-3},{-10,-3},{-9,-3},{-8,-3},{-7,-3},{-6,-3},{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},{ 6,-3},{ 7,-3},{ 8,-3},{ 9,-3},{ 10,-3},{ 11,-3},{ 12,-3},
		{-11,-4},{-10,-4},{-9,-4},{-8,-4},{-7,-4},{-6,-4},{-5,-4},{-4,-4},{-3,-4},{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},{ 5,-4},{ 6,-4},{ 7,-4},{ 8,-4},{ 9,-4},{ 10,-4},{ 11,-4},
				{-10,-5},{-9,-5},{-8,-5},{-7,-5},{-6,-5},{-5,-5},{-4,-5},{-3,-5},{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},{ 3,-5},{ 4,-5},{ 5,-5},{ 6,-5},{ 7,-5},{ 8,-5},{ 9,-5},{ 10,-5},
						{-9,-6},{-8,-6},{-7,-6},{-6,-6},{-5,-6},{-4,-6},{-3,-6},{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6},{ 3,-6},{ 4,-6},{ 5,-6},{ 6,-6},{ 7,-6},{ 8,-6},{ 9,-6},
								{-8,-7},{-7,-7},{-6,-7},{-5,-7},{-4,-7},{-3,-7},{-2,-7},{-1,-7},{ 0,-7},{ 1,-7},{ 2,-7},{ 3,-7},{ 4,-7},{ 5,-7},{ 6,-7},{ 7,-7},{ 8,-7},
										{-7,-8},{-6,-8},{-5,-8},{-4,-8},{-3,-8},{-2,-8},{-1,-8},{ 0,-8},{ 1,-8},{ 2,-8},{ 3,-8},{ 4,-8},{ 5,-8},{ 6,-8},{ 7,-8},
												{-6,-9},{-5,-9},{-4,-9},{-3,-9},{-2,-9},{-1,-9},{ 0,-9},{ 1,-9},{ 2,-9},{ 3,-9},{ 4,-9},{ 5,-9},{ 6,-9},
														{-5,-10},{-4,-10},{-3,-10},{-2,-10},{-1,-10},{ 0,-10},{ 1,-10},{ 2,-10},{ 3,-10},{ 4,-10},{ 5,-10},
																{-4,-11},{-3,-11},{-2,-11},{-1,-11},{ 0,-11},{ 1,-11},{ 2,-11},{ 3,-11},{ 4,-11},
																		{-3,-12},{-2,-12},{-1,-12},{ 0,-12},{ 1,-12},{ 2,-12},{ 3,-12}
};

const TileOffset* arrOffsetCircle[13] = 
{
	0,0,0,
	arrOffsetCircle3,
	arrOffsetCircle4,
	arrOffsetCircle5,
	arrOffsetCircle6,
	arrOffsetCircle7,
	arrOffsetCircle8,
	arrOffsetCircle9,
	arrOffsetCircle10,
	arrOffsetCircle11,
	arrOffsetCircle12
};

const ulong arrSizeCircle[13] = 
{
	0,0,0,
	Cricle3_Size,
	Cricle4_Size,
	Cricle5_Size,
	Cricle6_Size,
	Cricle7_Size,
	Cricle8_Size,
	Cricle9_Size,
	Cricle10_Size,
	Cricle11_Size,
	Cricle12_Size
};



/// 8方向上距离为3的扇面
const TileOffset arrOffsetSector3[eDirectionCount][Sector3_Size] =
{
	// EastSouth
	{
		{ 0, 3},{ 1, 3},
		{ 0, 2},{ 1, 2},{ 2, 2},
		{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},
				{ 1, 0},{ 2, 0},{ 3, 0},
		{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},
		{ 0,-2},{ 1,-2},{ 2,-2},
		{ 0,-3},{ 1,-3},
	},
	// East
	{
				{-1, 3},{ 0, 3},{ 1, 3},
		{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},
				{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},
								{ 1, 0},{ 2, 0},{ 3, 0},
								{ 1,-1},{ 2,-1},{ 3,-1},
										{ 2,-2},
	},
	// EastNorth
	{
						{-1, 3},{ 0, 3},{ 1, 3},
				{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},
		{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},
		{-3, 0},{-2, 0},{-1, 0},		{ 1, 0},{ 2, 0},{ 3, 0},
	},
	// North
	{
						{-1, 3},{ 0, 3},{ 1, 3},
				{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},
		{-3, 1},{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},
		{-3, 0},{-2, 0},{-1, 0},
		{-3,-1},{-2,-1},{-1,-1},
				{-2,-2},
	},
	// WestNorth
	{
						{-1, 3},{ 0, 3},
				{-2, 2},{-1, 2},{ 0, 2},
		{-3, 1},{-2, 1},{-1, 1},{ 0, 1},
		{-3, 0},{-2, 0},{-1, 0},
		{-3,-1},{-2,-1},{-1,-1},{ 0,-1},
				{-2,-2},{-1,-2},{ 0,-2},
						{-1,-3},{ 0,-3},
	},
	// West
	{
				{-2, 2},
		{-3, 1},{-2, 1},{-1, 1},
		{-3, 0},{-2, 0},{-1, 0},
		{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},
				{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},
						{-1,-3},{ 0,-3},{ 1,-3},
	},
	// WestSouth
	{
		{-3, 0},{-2, 0},{-1, 0},		{ 1, 0},{ 2, 0},{ 3, 0},
		{-3,-1},{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},
				{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},
						{-1,-3},{ 0,-3},{ 1,-3},
	},
	// South
	{
										{ 2, 2},
								{ 1, 1},{ 2, 1},{ 3, 1},
								{ 1, 0},{ 2, 0},{ 3, 0},
				{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},
		{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},
				{-1,-3},{ 0,-3},{ 1,-3},
	},
};


/// 8方向上身前5*6的矩形
const TileOffset arrOffsetFrontRect_5_6[eDirectionCount][FrontRect_5_6_Size] = 
{
	// EastSouth
	{
		{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},
		{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},
		{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},
		{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},
		{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},
	},
	// East
	{
								{ 2, 5},{ 3, 5},
						{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},
				{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},
		{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},
				{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},
						{ 1, 0},{ 2, 0},{ 3, 0},
								{ 2,-1},
	},
	// EastNorth
	{
		{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},
		{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},
		{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},
		{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},
		{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},
		{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},
	},
	// North
	{
						{-3, 5},{-2, 5},
				{-4, 4},{-3, 4},{-2, 4},{-1, 4},
		{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},
		{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},
				{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},
						{-3, 0},{-2, 0},{-1, 0},
								{-2,-1},
	},
	// WestNorth
	{
		{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},
		{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},
		{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},
		{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},
		{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},
	},
	// West
	{
								{-2, 1},
						{-3, 0},{-2, 0},{-1, 0},
				{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},
		{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},
		{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},
				{-4,-4},{-3,-4},{-2,-4},{-1,-4},
						{-3,-5},{-2,-5},
	},
	// WestSouth
	{
		{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},
		{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},
		{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},
		{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},
		{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},
		{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6},

	},
	// South
	{
								{ 2, 1},
						{ 1, 0},{ 2, 0},{ 3, 0},
				{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},
		{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},
				{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},
						{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},
								{ 2,-5},{ 3,-5},
	},
};


/// 8方向上身前5*9的矩形
const TileOffset arrOffsetFrontRect_5_9[eDirectionCount][FrontRect_5_9_Size] =
{
	// EastSouth
	{
		{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},{ 6, 2},{ 7, 2},{ 8, 2},{ 9, 2},
		{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},{ 5, 1},{ 6, 1},{ 7, 1},{ 8, 1},{ 9, 1},
		{ 1, 0},{ 2, 0},{ 3, 0},{ 4, 0},{ 5, 0},{ 6, 0},{ 7, 0},{ 8, 0},{ 9, 0},
		{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},{ 7,-1},{ 8,-1},{ 9,-1},
		{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},{ 6,-2},{ 7,-2},{ 8,-2},{ 9,-2},
	},
	// East
	{
														{ 5, 8},
												{ 4, 7},{ 5, 7},{ 6, 7},
										{ 3, 6},{ 4, 6},{ 5, 6},{ 6, 6},{ 7, 6},
								{ 2, 5},{ 3, 5},{ 4, 5},{ 5, 5},{ 6, 5},{ 7, 5},{ 8, 5},
						{ 1, 4},{ 2, 4},{ 3, 4},{ 4, 4},{ 5, 4},{ 6, 4},{ 7, 4},
				{ 0, 3},{ 1, 3},{ 2, 3},{ 3, 3},{ 4, 3},{ 5, 3},{ 6, 3},
		{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},{ 3, 2},{ 4, 2},{ 5, 2},
				{ 0, 1},{ 1, 1},{ 2, 1},{ 3, 1},{ 4, 1},
						{ 1, 0},{ 2, 0},{ 3, 0},
								{ 2,-1},
	},
	// EastNorth
	{
		{-2, 9},{-1, 9},{ 0, 9},{ 1, 9},{ 2, 9},
		{-2, 8},{-1, 8},{ 0, 8},{ 1, 8},{ 2, 8},
		{-2, 7},{-1, 7},{ 0, 7},{ 1, 7},{ 2, 7},
		{-2, 6},{-1, 6},{ 0, 6},{ 1, 6},{ 2, 6},
		{-2, 5},{-1, 5},{ 0, 5},{ 1, 5},{ 2, 5},
		{-2, 4},{-1, 4},{ 0, 4},{ 1, 4},{ 2, 4},
		{-2, 3},{-1, 3},{ 0, 3},{ 1, 3},{ 2, 3},
		{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},{ 2, 2},
		{-2, 1},{-1, 1},{ 0, 1},{ 1, 1},{ 2, 1},
	},
	// North
	{
								{-5, 8},
						{-6, 7},{-5, 7},{-4, 7},
				{-7, 6},{-6, 6},{-5, 6},{-4, 6},{-3, 6},
		{-8, 5},{-7, 5},{-6, 5},{-5, 5},{-4, 5},{-3, 5},{-2, 5},
				{-7, 4},{-6, 4},{-5, 4},{-4, 4},{-3, 4},{-2, 4},{-1, 4},
						{-6, 3},{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{ 0, 3},
								{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},{ 0, 2},{ 1, 2},
										{-4, 1},{-3, 1},{-2, 1},{-1, 1},{ 0, 1},
												{-3, 0},{-2, 0},{-1, 0},
														{-2,-1},
	},
	// WestNorth
	{
		{-9, 2},{-8, 2},{-7, 2},{-6, 2},{-5, 2},{-4, 2},{-3, 2},{-2, 2},{-1, 2},
		{-9, 1},{-8, 1},{-7, 1},{-6, 1},{-5, 1},{-4, 1},{-3, 1},{-2, 1},{-1, 1},
		{-9, 0},{-8, 0},{-7, 0},{-6, 0},{-5, 0},{-4, 0},{-3, 0},{-2, 0},{-1, 0},
		{-9,-1},{-8,-1},{-7,-1},{-6,-1},{-5,-1},{-4,-1},{-3,-1},{-2,-1},{-1,-1},
		{-9,-2},{-8,-2},{-7,-2},{-6,-2},{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},
	},
	// West
	{
														{-2, 1},
												{-3, 0},{-2, 0},{-1, 0},
										{-4,-1},{-3,-1},{-2,-1},{-1,-1},{ 0,-1},
								{-5,-2},{-4,-2},{-3,-2},{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},
						{-6,-3},{-5,-3},{-4,-3},{-3,-3},{-2,-3},{-1,-3},{ 0,-3},
				{-7,-4},{-6,-4},{-5,-4},{-4,-4},{-3,-4},{-2,-4},{-1,-4},
		{-8,-5},{-7,-5},{-6,-5},{-5,-5},{-4,-5},{-3,-5},{-2,-5},
				{-7,-6},{-6,-6},{-5,-6},{-4,-6},{-3,-6},
						{-6,-7},{-5,-7},{-4,-7},
								{-5,-8},
	},
	// WestSouth
	{
		{-2,-1},{-1,-1},{ 0,-1},{ 1,-1},{ 2,-1},
		{-2,-2},{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},
		{-2,-3},{-1,-3},{ 0,-3},{ 1,-3},{ 2,-3},
		{-2,-4},{-1,-4},{ 0,-4},{ 1,-4},{ 2,-4},
		{-2,-5},{-1,-5},{ 0,-5},{ 1,-5},{ 2,-5},
		{-2,-6},{-1,-6},{ 0,-6},{ 1,-6},{ 2,-6},
		{-2,-7},{-1,-7},{ 0,-7},{ 1,-7},{ 2,-7},
		{-2,-8},{-1,-8},{ 0,-8},{ 1,-8},{ 2,-8},
		{-2,-9},{-1,-9},{ 0,-9},{ 1,-9},{ 2,-9},
},
	// South
	{
								{ 2, 1},
						{ 1, 0},{ 2, 0},{ 3, 0},
				{ 0,-1},{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},
		{-1,-2},{ 0,-2},{ 1,-2},{ 2,-2},{ 3,-2},{ 4,-2},{ 5,-2},
				{ 0,-3},{ 1,-3},{ 2,-3},{ 3,-3},{ 4,-3},{ 5,-3},{ 6,-3},
						{ 1,-4},{ 2,-4},{ 3,-4},{ 4,-4},{ 5,-4},{ 6,-4},{ 7,-4},
								{ 2,-5},{ 3,-5},{ 4,-5},{ 5,-5},{ 6,-5},{ 7,-5},{ 8,-5},
										{ 3,-6},{ 4,-6},{ 5,-6},{ 6,-6},{ 7,-6},
												{ 4,-7},{ 5,-7},{ 6,-7},
														{ 5,-8},
	},
};



const TileOffset arrOffsetRadial[eDirectionCount] = 
{
	{ 1,  0},
	{ 1,  1},
	{ 0,  1},
	{-1,  1},
	{-1,  0},
	{-1, -1},
	{ 0, -1},
	{ 1, -1}
};

const TileOffset arrOffsetRadialOrigin_3[eDirectionCount][3] = 
{
	{ { 1,-1}, { 1, 0}, { 1, 1} },
	{ { 1, 0}, { 1, 1}, { 0, 1} },
	{ { 1, 1}, { 0, 1}, {-1, 1} },
	{ { 0, 1}, {-1, 1}, {-1, 0} },
	{ {-1, 1}, {-1, 0}, {-1,-1} },
	{ {-1, 0}, {-1,-1}, { 0,-1} },
	{ {-1,-1}, { 0,-1}, { 1,-1} },
	{ { 0,-1}, { 1,-1}, { 1, 0} }
};

const TileOffset arrOffsetRadialOrigin_5[eDirectionCount][5] = 
{
	{ { 1,-2}, { 1,-1}, { 1, 0}, { 1, 1}, { 1, 2} },
	{ { 2, 0}, { 1, 0}, { 1, 1}, { 0, 1}, { 0, 2} },
	{ {-2, 1}, {-1, 1}, { 0, 1}, { 1, 1}, { 2, 1} },
	{ { 0, 2}, { 0, 1}, {-1, 1}, {-1, 0}, {-2, 0} },
	{ {-1,-2}, {-1,-1}, {-1, 0}, {-1, 1}, {-1, 2} },
	{ { 0,-2}, { 0,-1}, {-1,-1}, {-1, 0}, {-2, 0} },
	{ {-2,-1}, {-1,-1}, { 0,-1}, { 1,-1}, { 2,-1} },
	{ { 0,-2}, { 0,-1}, { 1,-1}, { 1, 0}, { 2, 0} }
};