#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define NAME_LENGTH 10
#define TEL_LENGTH 10

struct abonent {
    char name[NAME_LENGTH];
    char second_name[NAME_LENGTH];
    char tel[TEL_LENGTH];
};

struct node {
    struct abonent data;
    struct node* prev;
    struct node* next;
};

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct node* create_node(const struct abonent* abonent) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }
    
    strncpy(new_node->data.name, abonent->name, NAME_LENGTH - 1);
    strncpy(new_node->data.second_name, abonent->second_name, NAME_LENGTH - 1);
    strncpy(new_node->data.tel, abonent->tel, TEL_LENGTH - 1);
    
    new_node->data.name[NAME_LENGTH - 1] = '\0';
    new_node->data.second_name[NAME_LENGTH - 1] = '\0';
    new_node->data.tel[TEL_LENGTH - 1] = '\0';
    
    new_node->prev = NULL;
    new_node->next = NULL;
    
    return new_node;
}

void add_abonent(struct node** head, struct node** tail) {
    struct abonent new_abonent;
    
    printf("\nДобавление нового абонента:\n");
    
    printf("Введите имя (макс. %d символов): ", NAME_LENGTH - 1);
    scanf("%9s", new_abonent.name);
    clear_input_buffer();
    
    printf("Введите фамилию (макс. %d символов): ", NAME_LENGTH - 1);
    scanf("%9s", new_abonent.second_name);
    clear_input_buffer();
    
    printf("Введите телефон (макс. %d цифр): ", TEL_LENGTH - 1);
    scanf("%9s", new_abonent.tel);
    clear_input_buffer();
    
    struct node* new_node = create_node(&new_abonent);
    if (new_node == NULL) {
        return;
    }
    
    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        (*tail)->next = new_node;
        new_node->prev = *tail;
        *tail = new_node;
    }
    
    printf("\nАбонент успешно добавлен!\n\n");
}

void delete_abonent(struct node** head, struct node** tail) {
    if (*head == NULL) {
        printf("\nСправочник пуст, удалять нечего.\n\n");
        return;
    }
    
    int index, count = 0;
    printf("\nВведите номер абонента для удаления: ");
    scanf("%d", &index);
    clear_input_buffer();
    
    if (index < 1) {
        printf("\nНеверный номер абонента.\n\n");
        return;
    }
    
    struct node* current = *head;
    while (current != NULL && ++count < index) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("\nНеверный номер абонента.\n\n");
        return;
    }
    
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        *tail = current->prev;
    }
    
    free(current);
    printf("\nАбонент успешно удален!\n\n");
}

void search_by_name(struct node* head) {
    if (head == NULL) {
        printf("\nСправочник пуст.\n\n");
        return;
    }
    
    char search_name[NAME_LENGTH];
    printf("\nВведите имя для поиска: ");
    scanf("%9s", search_name);
    clear_input_buffer();
    
    printf("\nРезультаты поиска:\n");
    printf("№  Имя      Фамилия   Телефон\n");
    printf("-----------------------------\n");
    
    bool found = false;
    struct node* current = head;
    int count = 0;
    
    while (current != NULL) {
        if (strcmp(current->data.name, search_name) == 0) {
            printf("%-2d %-9s %-9s %-9s\n", 
                   ++count, 
                   current->data.name, 
                   current->data.second_name, 
                   current->data.tel);
            found = true;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Абоненты с именем '%s' не найдены.\n", search_name);
    }
    printf("\n");
}

void print_all(struct node* head) {
    if (head == NULL) {
        printf("\nСправочник пуст.\n\n");
        return;
    }
    
    int count = 0;
    struct node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    printf("\nСписок всех абонентов (%d):\n", count);
    printf("№  Имя      Фамилия   Телефон\n");
    printf("-----------------------------\n");
    
    current = head;
    int index = 0;
    while (current != NULL) {
        printf("%-2d %-9s %-9s %-9s\n", 
               ++index, 
               current->data.name, 
               current->data.second_name, 
               current->data.tel);
        current = current->next;
    }
    printf("\n");
}

void free_list(struct node* head) {
    struct node* current = head;
    while (current != NULL) {
        struct node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct node* head = NULL;
    struct node* tail = NULL;
    int choice;
    
    do {
        printf("Меню:\n");
        printf("1) Добавить абонента\n");
        printf("2) Удалить абонента\n");
        printf("3) Поиск абонентов по имени\n");
        printf("4) Вывод всех записей\n");
        printf("5) Выход\n");
        printf("Выберите пункт меню: ");
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                add_abonent(&head, &tail);
                break;
            case 2:
                delete_abonent(&head, &tail);
                break;
            case 3:
                search_by_name(head);
                break;
            case 4:
                print_all(head);
                break;
            case 5:
                printf("\nВыход из программы.\n");
                break;
            default:
                printf("\nНеверный выбор. Попробуйте снова.\n\n");
        }
    } while (choice != 5);
    
    free_list(head);
    return 0;
}
