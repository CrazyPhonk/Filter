#include <stdio.h>

int main() {
    FILE *file;
    char filename[] = "AC⧸DC - Back In Black.wav";
    file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Ошибка открытия файлаn");
        return 1;
    }

    // Пропускаем заголовок файла
    fseek(file, 44, SEEK_SET);

    // Читаем данные из файла
    short buffer;
    while(fread(&buffer, sizeof(short), 1, file)) {
        // Обрабатываем данные, например, записываем их в массив
        // Добавьте нужный код
    }

    fclose(file);

    return 0;
}
