struct stu {
    int num;
    char name[10];
    int age;
};

void py(struct stu *p) { printf(“%s\n”, (*p).name); }

main() {
    struct stu student[3] = {{1001, “Sun”, 25},
                             {1002, “Ling”, 23},
                             {1003, “Shen”, 22}};
    py(student + 2);
}

