#include "linked_list.h"

#include <iostream>

int main()
{
    const int values[] = {7, 3, 9, 3, -2};
    constexpr std::size_t count = sizeof(values) / sizeof(values[0]);
    
    Node* list = createList(values, count);
    Node* copiedList = copyList(list);

    std::cout << "List size: " << listSize(list) << '\n';

    std::cout << "Copy successful: "
              << (areListsEqual(list, copiedList) ? "yes" : "no") << '\n';

    std::cout << "Initially sorted: "
              << (isSorted(list) ? "yes" : "no") << '\n';

    deleteList(list);
    deleteList(copiedList);

    return 0;
}
