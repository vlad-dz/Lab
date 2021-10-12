#include <iostream>
#include <queue>

using namespace std;


class Queue {
    public:
        /** 
         * Вставить значение в очередь.
         * @param value - значение, которое необходимо вставить.
         */
        void push(int value) {
            // Выделения памяти под временный массив.
            int *_temp = new int[size];
            // Копирование массива во временный.
            copy_array(_temp);
            // Увеличение размера очереди.
            size++;
            // Выделение памяти для нового массива с новым размером.
            val = new int[size];

            int oldSize = size - 1;
            // Заполнение старыми данными нового массива.
            for(int i = 0; i < oldSize; i++) {
                val[i] = _temp[i];
            }
            // Добавление в конец новго элемента.
            val[oldSize] = value;
        }
        
        /**
         * Проверить пустая ли очередь.
         * @return - true, если очередь пустая, иначе false.
         */
        bool empty() {
            return size == 0;
        }
        
        /**
         * Удалить послдний добаленный элемент из очереди.
         */
        void pop() {
            if(!empty()) {
                // Создание и инициализация временого массива.
                int *_temp = new int[size];
                copy_array(_temp);
                // Уменьшение размера очереди.
                size--;
                // Выделение памяти под новый массив с новым размером.
                val = new int[size];
                // Заполнение новго массива старыми данными, за 
                // исключением поледнего элемента.
                for(int i = 0; i < size; i++) {
                    val[i] = _temp[i + 1];
                }
            }
            
        }
        
        /**
         * Вернуть первый элемент из очереди.
         * @return - первый элемент очереди.
         */
        int front() {
            if(!empty()) {
                return val[0];
            }
            return -1;
        }
        
        /**
         * Вернуть последний элемент из очереди.
         * @return - последний элемент из очереди.
         */
        int back() {
            if(!empty()) {
                return val[size - 1];
            }
            return -1;
        }
        
        /**
         *  Печать очереди в консоль.
         */
        void print() {
            for(int i = 0; i < size; i++) {
                cout << val[i] << " ";
            }
            cout << "\n";
        }
        
        Queue operator+(Queue& q) {
            Queue result;
            
            while(!empty() || !q.empty()) {
                // Если обе очереди не пустые, то берем по значению и сравниваем.
                if(!empty() && !q.empty()) {
                    int value_from_first = front();
                    int value_from_second = q.front();
                    
                    if(value_from_first < value_from_second) {
                        result.push(value_from_first);
                        pop();
                    } else {
                        result.push(value_from_second);
                        q.pop();
                    }
                } else if (empty()) { // Если только первая пустая, а вторая нет.
                    int val = q.front();
                    result.push(val);
                    q.pop();
                } else { // Если только вторая пустая, а первая нет.
                    int val = front();
                    q.push(val);
                    pop();
                }
            }
            
            return result;
        }
        
    private: 
        // Указатель для хранения элементов очереди.
        int *val;
        // Переменная для хранения размера очереди.
        int size = 0;
        /**
         * Копирование текущей очереди в массив.
         * @param a - указатель, в который скопируется очередь.
         */
        void copy_array(int *a) {
            for(int i = 0; i < size; i++) {
                a[i] = val[i];
            }
        }
};

// Размер первой очереди.
int queue_first_size = 5;
// Размер второй очереди
int queue_second_size = 8;

// Обьявление функции инициализации очереди.
void init_queue(Queue &q, int size);

int main()
{
    Queue q_first;
    Queue q_second;

    // Инициализация двух очередей.
    init_queue(q_first, queue_first_size);
    init_queue(q_second, queue_second_size);
    
    // Вывод очередей в консоль.
    cout << "Первая очередь:" << "\n";
    q_first.print();
    cout << "\n" << "Вторая очередь:" << "\n";
    q_second.print();
    
    // Объединение двух очередей.
    Queue q_result = q_first + q_second;
    
    cout << "\n" << "Результат2" << "\n";
    q_result.print();
    
    return 0;
}

void init_queue(Queue &q, int size) {
    for(int i = 0; i < size; i++) {
        int v = rand() % size + 1;
        
        if(!q.empty()) {
            int last_value = q.back();
            v += last_value;
        } 
        q.push(v);
    }
}