//Student Num:21058644 | UWECyber | MSc in Cybesecurity
#include <stdlib.h>
#include <stdio.h>

//Declaring the functions
int rand_num();
void mean_test();
void freq_test();
void serial_test();
void poker_test();
void poker_file();
void poker_function(int num, int arg);

static FILE *fptr; // pointer of file type

int q_compar (const void * a, const void * b) { //pointer to a comparison function (qsort function)
   return ( *(int*)a - *(int*)b );
}

 // function to generate random number
int rand_num()
 {
    int random_number = (int)(10.0*rand()/(RAND_MAX+ 1.0));
    return random_number;
 }

//01.Mean Test
 void mean_test()
 {
    int num = 1000, sum = 0;
    int array[num]; //init array

    //generate 1000 random numbers
    for (int i = 0; i < num; i++)
    {
        array[i] = rand_num();
    }
   //calculate SUM each number in array
    for (int i = 0; i < num; i++)
    {
        sum += array[i];
    }
    //Calculate the Mean value
    float mean = sum /(float)num;
    printf("Mean of %d random numbers: %.2f\n", num, mean);
 }

//02.Frequency Test
 void freq_test()
 {
   int num = 10000;
   int array[num];

   //generate 10000 random numbers
   for (int i = 0; i < num; i++)
   {
      array[i] = rand_num();
   }
   
   int n = sizeof array / sizeof array[0]; //get the size of array
   int frequency[n]; //Declare another array to store frequency of the element

   for (int i = 0; i < n; i++)
   {
      frequency[i] = -1; //initialize frequencies to -1
   }
   //count the frequency of each element in the array
   for (int i = 0; i < n; i++)
   {
      int count = 1;
      for (int j = i+1; j < n; j++)
      {
         if (array[i] == array[j]) //Check the duplicate numbers
         {
            count++;
            frequency[j] = 0; //not to count same frequency number again
         }
      }
      if (frequency[i] != 0) //If frequency of current element is not counted
      {
         frequency[i]=count;
      }
   }
   printf("The Frequency of the elements in this Array is : \n");
   printf("-----------------------------------\n");
   printf(" Element |  Frequency  |  Percentage\n");
   printf("-----------------------------------\n");
   for (int i = 0; i < n; i++)
   {
      if (frequency[i] != 0)
      {
         //printf("%d Occurs %d Times \n", array[i], frequency[i]);
         printf("  %d\t", array[i]);
         printf(" | ");
         printf("  %d\t", frequency[i]);
         printf(" | ");
         printf("  %.2f%%\n", (float)frequency[i] / n * 100);
      }
   }  
 }

 //03. Serial Test
 void serial_test()
 {
     int num = 10000, number;
     int array[num][2];  // 2D array declaration

     struct num_struct    // this structure will store numbers 00 to 99
     {
        int count[100];
        double frequency[100];
     };
     
     struct num_struct num_stats; //declaring variables of struct

     for (int i = 0; i < 100; i++) //initialize the count stats to 0
     {
        num_stats.count[i] = 0;
     }

     for (int i = 0; i < num; i++) //generate random number
     {
        array[i][0] = rand_num();
        array[i][1] = rand_num();

        number = array[i][0]*10 + array[i][1]; //this will create num pair
        num_stats.count[number] += 1; //update the count of pair
     }
     
     printf("---------------------------\n");
     printf("Number pairs  |  Frequency\n");
     printf("---------------------------\n");

     for (int i = 0; i < 100; i++)
     {
        num_stats.frequency[i] = (num_stats.count[i]*1.0 / num) * 100; //calculate the presentage

        if (i < 10)
            printf("%02d\t\t %.2f%%\n", i, num_stats.frequency[i]);
        else
            printf("%d\t\t %.2f%%\n", i, num_stats.frequency[i]);
     }
     
 }
 //4. Pocker test
 void poker_test()
 {
    int num = 1000;
    int arg = 4;
    poker_function(num,arg);
 }
 //5. Pocker test from file
 void poker_file()
 {
    int num = 1000;
    int arg = 5;
    poker_function(num, arg);
 }

//default function to the pocker test
 void poker_function(int num, int arg)
{
    int array[num][4];
    int count[5] = {0,0,0,0,0};

    if (arg == 4) //pocker test argument 
    {
        if ((fptr = fopen("poker_numbers.txt", "w")) == NULL) //file writing
    {
        printf("Error!! operning poker number file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            array[i][j] = rand_num(); //generate and store random numbers
            fprintf(fptr, "%d", array[i][j]);
        }
        fputc('\n', fptr); //print numbers in new line
    }
    fclose(fptr);
    }
    else if (arg == 5)
    {
        if ((fptr = fopen("poker_numbers.txt", "r")) == NULL)
        {
            printf("Error!! operning poker number file");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < 4; j++) // read the numbers line by line in the file
            {
                array[i][j] = fgetc(fptr) - '0'; //convert ascii to int
            }
            
            fgetc(fptr);   //read the newline 
        }
        fclose(fptr); //close the file 
    }

    for (int i = 0; i < num; i++)
    {
        //create an array for sort the sequence
        int num_arr[] = {array[i][0], array[i][1], array[i][2], array[i][3]};

        qsort(num_arr, 4, sizeof(int), q_compar); //qsort to sort int values

        //define boolean varibale for identify pocker pattern 
        int all_same = (num_arr[0] == num_arr[1] && num_arr[1] == num_arr[2]
                        && num_arr[2] == num_arr[3]);
        int three_of_kind = (num_arr[0] == num_arr[1] == num_arr[2])
                            || (num_arr[1] == num_arr[2] == num_arr[3]);
        int one_pair = (num_arr[0] == num_arr[1]) || (num_arr[1] == num_arr[2])
                            || (num_arr[2] == num_arr[3]);
        
        
        if (all_same) //all of kind - 1111 All Same
        {
            count[0] +=1;
        }
        else if (!all_same && three_of_kind) //three digits the same
        {
            count[1] += 1;
        }
        else if (num_arr[0] == num_arr[1] && num_arr[2] == num_arr[3]) //two pairs are the same
        {
            count[2] += 1;
        }
        else if (!all_same && !three_of_kind && one_pair) //one pair the same
        {
            count[3] += 1;
        }
        else //none identical
            count[4] += 1;
    }

    char str[5][1024];

    printf("-----------------------------------------------------------------------\n");
    printf("|\tCategory\t\t\t\t| Frequency | Percent |\n");
    printf("-----------------------------------------------------------------------\n");

    printf("%-48s", "|1.) all the same");
    printf("|%5s%d%5s", " ", count[0], " ");
    printf("|%2s%.2f%%%s |\n", " ", (count[0]*1.0 / 100), " ");

    printf("%-48s", "|2.) 3 digits the same ");
    printf("|%5s%d%4s", " ", count[1], " ");
    printf("|%2s%.2f%%%s |\n", " ", (count[1]*1.0 / 100), " ");

    printf("%-48s", "|3.) two pairs ");
    printf("|%5s%d%4s", " ", count[2], " ");
    printf("|%2s%.2f%%%s |\n", " ", (count[2]*1.0 / 100), " ");

    printf("%-48s", "|4.) one pair ");
    printf("|%5s%d%3s", " ", count[3], " ");
    printf("|%2s%.2f%%%s |\n", " ", (count[3]*1.0 / 100), " ");

    printf("%-48s", "|5.) none identical");
    printf("|%5s%d%4s", " ", count[4], " ");
    printf("|%2s%.2f%%%s |\n", " ", (count[4]*1.0 / 100), " ");
    
}

int main (int argc, char *argv[])  //main function
{

    int choice;

    if(argc < 2) //check arg count
    {
        printf("Please provide an argument. Ex: %s [arg]\n", argv[0]);
    }
    else
    {
      choice = (int) atoi(argv[1]);

        switch (choice)
        {
        case 1:
            mean_test();
            break;
        case 2:
            freq_test();
            break;
        case 3:
            serial_test();
            break;
        case 4:
            poker_test();
            break;
        case 5:
            poker_file();
            break;
        default:
            printf("Something wrong!!");
            break;
        }
    }
    return 0;
}