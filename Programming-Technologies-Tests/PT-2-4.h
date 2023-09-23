#pragma once

#include <iostream>
#include <vector>

#include "Utils.h"

using namespace std;

namespace TASK_2_4
{
    // Элемент двусвязного списка
    struct Node
	{
		int value;
		Node* next;
		Node* prev;

		Node(int value) : value(value), next(nullptr) {}
	};

    // Двусвязный список
    class List
    {
    public:
        List() : _size(0), _tail(nullptr), _head(nullptr) { }
        ~List() { clear(); }

        // Добавление элемента в конец списка
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
        // Добавление элемента в начало списка
        void push_front(int element)
        {
            Node* newElement = new Node(element);

            if (_head == nullptr)
            {
                _head = newElement;
                _tail = _head;
            }
            else
            {
                newElement->next = _head;
                _head->prev = newElement;
                _head = newElement;
            }

            ++_size;
        }

        // Удаление элемента из конца списка
        int pop_back()
        {
            Node* deletedNode = _tail;
            int deletedValue = deletedNode->value;
            
            _tail = _tail->prev;
            delete deletedNode;

            --_size;

            if (_size == 1)
            {
                _tail->next = nullptr;
                _tail->prev = nullptr;
                _head->next = nullptr;
                _head->prev = nullptr;
            }
            return deletedValue;
        }

        // Очищение списка
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

        // Возвращает размер списка
        int size() { return _size; }

        // Возвращает первый элемент списка
        Node* get_head() { return _head; }
        // Возвращает последний элемент списка
        Node* get_tail() { return _tail; }

    private:
        Node* _head;
        Node* _tail;
        int _size;
    };

    struct Matrix
    {
    public:
        int N = 0, M = 0;
        int ** values = nullptr;

        Matrix(int N, int M) : N(N), M(M)
        {
            if (N == 0 || M == 0)
            {
                print_error("Cannot create matrix. Incorrect size given: N = " + to_string(N) + " M = " + to_string(M));
                return;
            }

            values = new int* [N];

            for (size_t i = 0; i < N; i++)
            {
                values[i] = new int[M];
            }
        }
        ~Matrix()
        {

        }
    };

    struct CSMatrix
    {
        int N = 0;
        List A;
        List LJ;
        List LI;

        CSMatrix* update()
        { 
            N = A.size(); 
            return this;
        }

        void print()
        {
            update();
            string outputString = "CSMatrix:\nN:\t";

            for (size_t i = 0; i < N; i++)
            {
                outputString += to_string(i + 1) + " ";
            }

            cout << outputString << "\n\n";

            outputString = "A:\t";
            Node* currentElement = A.get_head();
            while (currentElement)
            {
                outputString += to_string(currentElement->value) + " ";
                currentElement = currentElement->next;
            }
            cout << outputString << "\n";

            outputString = "LJ:\t";
            currentElement = LJ.get_head();
            while (currentElement)
            {
                outputString += to_string(currentElement->value) + " ";
                currentElement = currentElement->next;
            }
            cout << outputString << "\n";

            outputString = "LI:\t";
            currentElement = LI.get_head();
            while (currentElement)
            {
                outputString += std::to_string(currentElement->value) + " ";
                currentElement = currentElement->next;
            }
            cout << outputString << "\n";
        }

        vector<vector<int>> to_vector()
        {
            vector<vector<int>> output;

            vector<int> a;
            Node* currentElement = A.get_head();
            while (currentElement)
            {
                a.push_back(currentElement->value);
                currentElement = currentElement->next;
            }
            output.push_back(a);


            vector<int> lj;
            currentElement = LJ.get_head();
            while (currentElement)
            {
                lj.push_back(currentElement->value);
                currentElement = currentElement->next;
            }
            output.push_back(lj);

            vector<int> li;
            currentElement = LI.get_head();
            while (currentElement)
            {
                li.push_back(currentElement->value);
                currentElement = currentElement->next;
            }
            output.push_back(li);

            return output;
        }
    };

    Matrix* vectors_to_matrix(vector<vector<int>>& matrixVector)
    {
        int n = 0, m = 0;

        n = matrixVector.size();
        if (n == 0)
        {
            print_error("Cannot create matrix from vector. Incorrect size given: N = " + to_string(n));
            throw new exception("Error while creating Matrix from vector", -100);
        }

        m = matrixVector[0].size();
        if (m == 0)
        {
            print_error("Cannot create matrix from vector. Incorrect size given: M = " + to_string(m));
            throw new exception("Error while creating Matrix from vector", -100);
        }

        Matrix* maxtrixArray = new Matrix(n, m);

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
            {
                maxtrixArray->values[i][j] = matrixVector[i][j];
            }
        }
        return maxtrixArray;
    }

    vector<vector<int>>& matrix_to_vector(Matrix* matrix)
    {
        static vector<vector<int>> outputVector;

        for (size_t i = 0; i < matrix->N; i++)
        {
            vector<int> lineVector;
            outputVector.push_back(lineVector);
            for (size_t j = 0; j < matrix->M; j++)
            {
                outputVector[i][j] = matrix->values[i][j];
            }
        }
        return outputVector;
    }

    CSMatrix* pack_to_CSMatrix_with_shift(Matrix* inputMatrix)
    {
        CSMatrix* matrix = new CSMatrix;

        int n = inputMatrix->N;
        int m = inputMatrix->M;

        List& A = matrix->A;
        List& LI = matrix->LI;
        List& LJ = matrix->LJ;

        bool isLastNotNull = false;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
            {
                int element = inputMatrix->values[i][j];
                int iIndex = i + 1;
                int jIndex = j + 1;
                if (element == 0)
                {
                    continue;
                }

                ++jIndex;
                if (jIndex > m)
                {
                    jIndex = 1;
                    if (iIndex == n)
                    {
                        iIndex = 1;
                        isLastNotNull = true;
                    }
                    else
                    {
                        ++iIndex;
                    }
                }

                A.push_back(element);
                LI.push_back(iIndex);
                LJ.push_back(jIndex);
            }
        }

        if (isLastNotNull)
        {
            A.push_front(A.pop_back());
            LI.push_front(LI.pop_back());
            LJ.push_front(LJ.pop_back());
        }

        return matrix->update();
    }

    CSMatrix* pack_to_CSMatrix_with_shift(vector<vector<int>>& vectors)
    {
        return pack_to_CSMatrix_with_shift(vectors_to_matrix(vectors));
    }
}