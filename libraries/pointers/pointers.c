#define MAX 5
#define SEVENFOLD(nr) (nr * 7)
void printArray(int arr[])
{
    printf("Content of array: \n");
    for (int i = 0; i < MAX; i++)
    {
        printf("Address: %p has value: %d \n", &arr[i], arr[i]);
    }
}
void makeArray(int *arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        *(arr + i) = SEVENFOLD(i);
    }
}
void printFirstLetters(char *arr[][10])
{
    for (int i = 0; i < 6; i++)
    {
        printf("%c", *(arr[i]));
    }
}