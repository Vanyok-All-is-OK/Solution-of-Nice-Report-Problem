Условия:
Андрей занимается анализом графа подписок в одной социальной сети. Этот граф является ориентированным: если пользователь a подписан на пользователя b, то пользователь b не обязательно подписан на пользователя a.

Менеджер Андрея попросил его посчитать для каждого пользователя x, сколько существует пользователей y, таких, что от пользователя x можно добраться в графе подписок до пользователя y.

Печатать точное значение не имеет смысла, потому что оно смотрится некрасиво и моментально устареет, поэтому, вас интересует лишь примерное значение. Выполните задание менеджера и найдите эти значения с ошибкой не более чем в два раза.

Формат ввода
В первой строке заданы целые числа n и m (1 ≤ n, m ≤ 200 000) — число пользователей социальной сети и число ситуаций, когда один пользователь подписан на другого.

Далее, в m строках идёт описание графа, i-я из этих строк содержит два целых числа ai и bi (1 ≤ ai, bi ≤ n, ai ≠ bi) и означает, что пользователь ai подписан на пользователя bi. Каждая упорядоченная пара (ai, bi) встречается во входных данных не более одного раза.

Формат вывода
Выведите n целых чисел qi — оценку на количество пользователей y, таких, что от пользователя i можно добраться в графе подписок до пользователя y. Если настоящее количество таких пар равно zi, должны выполняться неравенства qi ≤ 2zi и zi ≤ 2qi. Кроме того, допустимо для не более, чем 10 пользователей вывести qi, не удовлетворяющее указанным ограничениям.

Примечание: жюри использует для проверки ваших ответов точное количество искомых пользователей. При этом жюри не гарантирует, что точное число можно найти, уложившись в ограничения по времени и памяти, и рекомендует использовать возможность вывести приблизительное значение.

В примере от пользователя 1 можно добраться до всех пяти пользователей. Однако, показанный ответ 7 тоже допустим, так как отличается от 5 не более, чем в два раза. Аналогично, допустимым является ответ 2 для пользователя 4.
