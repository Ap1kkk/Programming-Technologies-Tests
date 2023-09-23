#pragma once

#include <vector>

using namespace std;

namespace TASK_1_4
{
    // ������� ����������� ������
    struct Node
    {
        int value;
        Node* next;
        Node* prev;
        Node(int value) : next(nullptr), prev(nullptr)
        {
            this->value = value;
        }
    };

    // ���������� ������
    class List
    {
    public:
        List() : _size(0), _tail(nullptr), _head(nullptr) { }
        ~List() { clear(); }
        
        // ���������� �������� � ����� ������
        void push_back(int element)
        {
            Node* newElement = new Node(element);

            if (_head == nullptr)
            {
                _head = newElement;
                _tail = _head;
            }
            else
            {
                _tail->next = newElement;
                newElement->prev = _tail;
                _tail = _tail->next;
            }

            ++_size;
        }

        // �������� ������
        void clear()
        {
            if (_head == nullptr)
            {
                return;
            }

            Node* current = _head;
            while (_head->next)
            {
                current = _head->next;
                delete _head;
                _head = current;
            }
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            _size = 0;
        }

        // ���������� ������ ������
        int size() { return _size; }

        // ���������� ������ ������� ������
        Node* get_head() { return _head; }
        // ���������� ��������� ������� ������
        Node* get_tail() { return _tail; }

    private:
        Node* _head;
        Node* _tail;
        int _size;
    };

    // ������� ������� � ������
    List& vector_to_list(vector<int>& vect)
    {
        static List list;
        list.clear();

        for (size_t i = 0; i < vect.size(); i++)
        {
            list.push_back(vect[i]);
        }

        return list;
    }
    // ������� ������ � ������
    vector<int>& list_to_vector(List& list)
    {
        static vector<int> vect;
        vect.clear();

        Node* currentElement = list.get_head();
        while (currentElement->next)
        {
            vect.push_back(currentElement->value);
            currentElement = currentElement->next;
        }
        vect.push_back(currentElement->value);

        return vect;
    }

    // �������, ���������� ������ ������� ������ �� ��������� ��������� �������, 
    // ������� ��� ��� 0 ���� ������ �������� �� ����������
    List& swap_to_closet_max(List& list)
    {
        int lastListIndex = list.size() - 1;

        Node* lastElement = list.get_tail();

        int max = lastElement->value;
        int temp = max;

        lastElement->value = 0;

        Node* currentElement = lastElement;

        while (currentElement->prev)
        {
            currentElement = currentElement->prev;

            int currentValue = currentElement->value;
            if (currentValue < temp)
            {
                currentElement->value = temp;
                temp = currentValue;
            }
            else if (currentValue < max)
            {
                currentElement->value = max;
                temp = currentValue;
            }
            else if (currentValue >= max)
            {
                currentElement->value = 0;
                max = currentValue;
                temp = currentValue;
            }

        }

        return list;
    }

    // �������, ���������� ������ ������� ������ �� ��������� ��������� �������, 
    // ������� ��� ��� 0 ���� ������ �������� �� ����������
    // ������������ ������ ��� ������
    vector<int> swap_to_closet_max(vector<int>& vector)
    {
        List& list = swap_to_closet_max(vector_to_list(vector));
        return list_to_vector(list);
    }

}