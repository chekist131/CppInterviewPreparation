#pragma once

struct node
{
	int data;
	node* next;
	node(int _data, node* _next) : data{ _data }, next{ _next } {}
	node(int _data) : data{ _data }, next{ nullptr } {}
};