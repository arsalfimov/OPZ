#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <locale.h>

using namespace std;

// Функция, которая проверяет, является ли токен оператором
bool isOperator(const string& token) 
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

// Функция, которая проверяет, является ли токен числом
bool isNumber(const string& token) 
{
    return (token.find_first_not_of("0123456789") == string::npos);
}

// Функция, которая вычисляет значение выражения в ОПЗ
double evaluateExpression(const string& input) 
{
    stack<double> s; // создаем стек
    stringstream ss(input); // создаем строковый поток

    string token;
    while (getline(ss, token, ' ')) // разбиваем строку на символы
    {
        if (isNumber(token)) // если текущий символ - число, помещаем его в стек
        {
            s.push(stoi(token));
        }
        else if (isOperator(token)) // если текущий символ - оператор, извлекаем из стека два операнда и выполняем соответствующую операцию
        {
            if (s.size() < 2) // если в стеке менее двух операндов, то выражение некорректно
            {
                throw runtime_error("Invalid expression"); // выброс исключения с сообщением об ошибке
            }
            double x = s.top(); // извлекаем последний операнд
            s.pop();
            double y = s.top(); // извлекаем предпоследний операнд
            s.pop();

            if (token == "/" && x == 0)
            {
                throw runtime_error("Division by zero"); // выброс исключения с сообщением об ошибке
            }

            switch (token[0])   // Выбор операции в зависимости от переданного символа
            {
                case '+':
                    s.push(y + x);
                    break;
                case '-':
                    s.push(y - x);
                    break;
                case '*':
                    s.push(y * x);
                    break;
                case '/':
                    s.push(y / x);
                    break;
                default: // если токен не является допустимым оператором, выражение некорректно
                    throw runtime_error("Invalid expression");
            }
        }
        else // если токен не является ни числом, ни оператором, то выражение
        {
            // Неизвестный токен, формула некорректна
            throw runtime_error("Invalid expression");
        }
    }
    // В стеке должен остаться ровно один элемент, результат вычисления формулы
    if (s.size() != 1) 
    {
        throw runtime_error("Invalid expression");
    }
    return s.top();
}
//функция проверки выражения, является ли оно корректным
bool isValidExpression(const string& input) 
{
    try 
    {
        evaluateExpression(input); // Попытаемся вычислить выражение
        return true; // Если успешно, то выражение корректно
    } 
    catch (const runtime_error& e) 
    {
        // Если словили ошибку, то оно некорректно
        return false;
    }
}

int main() 
{
    // Устанавливаем русскую локаль, чтобы корректно отображать русские символы в консоли
    setlocale(LC_ALL, "Russian");

    // Запрашиваем у пользователя ввод формулы в обратной польской записи
    string input;
    cout << "Введите формулу в обратной польской записи: ";
    getline(cin, input);

    // Проверяем, является ли введенная формула корректной, используя функцию isValidExpression
    if (isValidExpression(input)) 
    {
        try 
        {
            // Если формула корректна, вычисляем ее значение с помощью функции evaluateExpression
            double result = evaluateExpression(input);
            cout << "Результат: " << result << endl;
        } 
        catch (const runtime_error& e) 
        {
            // Если при вычислении формулы возникла ошибка, выводим сообщение об ошибке
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    else 
    {
        // Выводим сообщение об ошибке
        cout << "Введенная формула некорректна" << endl;
    }
    system("pause");
    return 0;
}