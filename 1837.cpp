/** Description
 * 1837. Число Исенбаева
 * Ограничение времени: 0.5 секунды
 * Ограничение памяти: 64 МБ
 *
 * Владислав Исенбаев — двукратный чемпион Урала по программированию, вице-чемпион
 * TopCoder Open 2009, абсолютный чемпион ACM ICPC 2009. За то время,
 * которое вы потратите на чтение этого условия, Владислав уже решил бы одну задачу.
 * А может, и две…
 * Поскольку Владислав Исенбаев — выпускник СУНЦ УрГУ, неудивительно, что многие из бывших
 * и действующих олимпиадников УрГУ знакомы с ним уже много лет. Некоторые из них с
 * гордостью заявляют, что играли с Владиславом в одной команде.
 * Или играли в команде с бывшими однокомандниками Владислава…
 * Определим число Исенбаева следующим образом. У самого Владислава это число равняется
 * нулю. У тех, кто играл с ним в одной команде, оно равняется единице. У тех, кто играл
 * вместе с однокомандниками Владислава, но не играл с ним самим, это число равняется
 * двум, и так далее. Помогите автоматизировать процесс вычисления чисел Исенбаева,
 * чтобы каждый олимпиадник в УрГУ мог знать, насколько близок он к чемпиону ACM ICPC.
 * Исходные данные:
 * В первой строке записано целое число n — количество команд (1 ≤ n ≤ 100).
 * В каждой из следующих n строк записаны составы этих команд в виде фамилий трёх
 * участников. Фамилия каждого участника — непустая строка, состоящая из английских букв,
 * длиной не более 20 символов. Первая буква фамилии — заглавная,
 * все остальные — строчные. Фамилия Владислава — «Isenbaev».
 *
 * Результат:
 * Для каждого участника, представленного во входных данных, выведите в отдельной строке
 * через пробел его фамилию и число Исенбаева. Если это число не определено, выведите
 * вместо него «undefined». Участники должны быть упорядочены по фамилии в
 * лексикографическом порядке.
 *
 * Пример:
 * исходные данные
 * 7
 * Isenbaev Oparin Toropov
 * Ayzenshteyn Oparin Samsonov
 * Ayzenshteyn Chevdar Samsonov
 * Fominykh Isenbaev Oparin
 * Dublennykh Fominykh Ivankov
 * Burmistrov Dublennykh Kurpilyanskiy
 * Cormen Leiserson Rivest
 *
 * Pезультат:
 * Ayzenshteyn 2
 * Burmistrov 3
 * Chevdar 3
 * Cormen undefined
 * Dublennykh 2
 * Fominykh 1
 * Isenbaev 0
 * Ivankov 2
 * Kurpilyanskiy 3
 * Leiserson undefined
 * Oparin 1
 * Rivest undefined
 * Samsonov 2
 * Toropov 1
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <set>
 
int main()
{
	const int N = 111;

	std::set<std::string> all;
	std::set<std::string> used;
	std::map<std::string, unsigned int> d;
	std::string s[N][3];
	unsigned int n;

    std::cin >> n;
    std::string enter;
    getline(std::cin, enter);
 
    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            std::cin >> s[i][j];
            all.insert(s[i][j]);
        } 
        getline(std::cin, enter);
    }
 
    d["Isenbaev"] = 0;
    used.insert("Isenbaev");
    std::queue<std::string> q;
    q.push("Isenbaev");
 
    while (!q.empty()) {
        std::string v = q.front();
        q.pop();
        unsigned int dist = d[v];
 
        for (unsigned int i = 0; i < n; ++i) {
            bool find = false;
            for (unsigned int j = 0; j < 3; ++j)
                find |= (s[i][j] == v);
 
            if (find) {
                for (unsigned int j = 0; j < 3; ++j) {
                    std::string to = s[i][j];
                    if (used.find(to) == used.end()) {
                        used.insert(to);
                        q.push(to);
                        d[to] = dist + 1;
                    }
                }
            }
        }
    }
 
    for (auto it : all) {
        std::string name = it;
        std::cout << name << ' ';
        if (used.find(name) == used.end())
            std::cout << "undefined" << std::endl;
        else
            std::cout << d[name] << std::endl;
    }
 
    return 0;
}

