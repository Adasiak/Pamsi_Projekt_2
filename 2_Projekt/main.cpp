#include <iostream>
#include <ios>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
#include <cstddef>
#include <fstream>
#include "movie.hpp"

using namespace std;

//bad implementation - something does not work, not used
int qs_divaid (movie* tab, int start, int stop){ 
    movie pivot = tab[start];//setting an element from an array as pivot

    int smaller=0;
    for( int i=start+1; i<=stop; i++){  //for counts how many smaller values are than the value of pivot to put it in the right place
        if(tab[i].rate<=pivot.rate)
            smaller++;
    }   
    int pv_index=start+smaller;

    cout<<"calculation of how many smaller\n";
    //swap the pivot positions to the calculated position
    movie temp=tab[pv_index];
    tab[pv_index]=pivot;
    tab[start]=temp;
    cout<<"pivot swap\n";

    //sorting on the left and right side of the pivot (which are smaller - left and vice versa)
    int i=start, j=stop;
    while(i<pv_index && j>pv_index){
        while(tab[i].rate<=pivot.rate){
            i++;
        }
        while(tab[j].rate>pivot.rate){
            j++;   
        }
        if(i<pv_index && j>pv_index){
            temp=tab[i];
            tab[i]=tab[j];
            tab[j]=temp;
        }
    }
    cout<<"sort by pivot\n";
    return pv_index;
};


void quicksort(movie* tab, int start, int stop){
    if(stop <= start){
        return;
    }
    int i = start -1;
    int j = stop+1;
    float pivot = tab[(start + stop)/ 2].rate;
    while(1){
        while(pivot > tab [++i].rate);

        while(pivot < tab[--j].rate);
        if( i<= j){
            movie pom =tab[i];
            tab[i]=tab[j];
            tab[j]=pom;
        }
        else{
            break;
        }
    }
    if (j>start){
        quicksort(tab, start, j);
    }
    if (i < stop){
        quicksort(tab, i, stop);
    }
};

void merge_sort(movie* tab, int left, int center, int right){
    
    //count size of temp tab 
    int size_of_left_tab = (center - left + 1 );
    int size_of_right_tab = (right-center);
    
   
    //create temp tab
    movie* left_temp_tab = new movie[size_of_left_tab];
    movie* right_temp_tab = new movie[size_of_right_tab];

    //write to temp tab
    for(int i =0; i<size_of_left_tab; i++){
        left_temp_tab[i].name=tab[left+i].name;
        left_temp_tab[i].rate=tab[left+i].rate;
    }
    for(int j=0; j<size_of_right_tab; j++){
        right_temp_tab[j].name=tab[center+1+j].name;
        right_temp_tab[j].rate=tab[center+1+j].rate;
    }

    int left_count = 0;
    int right_count = 0;
    int tab_place = left;

    while (left_count < size_of_left_tab && right_count < size_of_right_tab){
        if(left_temp_tab[left_count].rate <= right_temp_tab[right_count].rate){
            tab[tab_place].rate = left_temp_tab[left_count].rate;
            tab[tab_place].name = left_temp_tab[left_count].name;
            left_count++;
        }
        else{
            tab[tab_place].rate = right_temp_tab[right_count].rate;
            tab[tab_place].name = right_temp_tab[right_count].name;
            right_count++;
        }    
        tab_place++;
    }
    
    //the case where on the right tab the elements end and on the left tab they are still
    while (left_count < size_of_left_tab)
    {
        tab[tab_place].rate = left_temp_tab[left_count].rate;
        tab[tab_place].name = left_temp_tab[left_count].name;
        left_count++;
        tab_place++;
    }
    

    //the case when on the left tab the elements end and on the right there are still
    while (right_count < size_of_right_tab)
    {
        tab[tab_place].rate = right_temp_tab[right_count].rate;
        tab[tab_place].name = right_temp_tab[right_count].name;
        right_count++;
        tab_place++;
    }
    delete[] left_temp_tab;
    delete[] right_temp_tab;
};

void divaid_mgs(movie* tab, int start, int stop){
    if(start >= stop){
        return;
    }
    int sr = start + (stop - start) / 2;
    divaid_mgs(tab, start, sr);
    divaid_mgs(tab, sr+1, stop);
    merge_sort(tab, start, sr, stop);
};

void bucket_sort(movie* tab, int length){
    movie** bucket = new movie* [5]; //creating two-dimensional arrays, dividing the table into 5 buckets
    int first = 0;
    int second = 0;
    int third = 0;
    int fourth = 0;
    int fifth = 0;
    //counting items for individual buckets
    for(int i = 0; i< length; i++){
        if(tab[i].rate == 1 || tab[i].rate == 2){
            first++;
        }
        if(tab[i].rate == 3 || tab[i].rate == 4){
            second++;
        }
        if(tab[i].rate == 5 || tab[i].rate == 6){
            third++;
        }
        if(tab[i].rate == 7 || tab[i].rate == 8){
            fourth++;
        }
        if(tab[i].rate == 9 || tab[i].rate == 10){
            fifth++;
        }
    }

    //creating buckets of a given size
    bucket[0] = new movie[first];
    bucket[1] = new movie[second];
    bucket[2] = new movie[third];
    bucket[3] = new movie[fourth];
    bucket[4] = new movie[fifth];

    //reset counters for filling in buckets
    first = 0;
    second = 0;
    third = 0;
    fourth = 0;
    fifth = 0;
    
     for(int k = 0; k< length; k++){
        if(tab[k].rate == 1 || tab[k].rate == 2){
            bucket[0][first].rate=tab[k].rate;
            bucket[0][first++].name=tab[k].name;
        }
        if(tab[k].rate == 3 || tab[k].rate == 4){
            bucket[1][second].rate=tab[k].rate;
            bucket[1][second++].name=tab[k].name;
        }
        if(tab[k].rate == 5 || tab[k].rate == 6){
            bucket[2][third].rate=tab[k].rate;
            bucket[2][third++].name=tab[k].name;
        }
        if(tab[k].rate == 7 || tab[k].rate == 8){
            bucket[3][fourth].rate=tab[k].rate;
            bucket[3][fourth++].name=tab[k].name;
        }
        if(tab[k].rate == 9 || tab[k].rate == 10){
            bucket[4][fifth].rate=tab[k].rate;
            bucket[4][fifth++].name=tab[k].name;
        }
    }

    //quicksort sort for each bucket
    quicksort(bucket[0], 0, first-1);
    quicksort(bucket[1], 0, second-1);
    quicksort(bucket[2], 0, third-1);
    quicksort(bucket[3], 0, fourth-1);
    quicksort(bucket[4], 0, fifth-1);

    //entering sorted buckets into the array
    int z = 0;
    int j = 0;
        while (first >0){
            tab[j].rate = bucket[0][z].rate;
            tab[j].name = bucket[0][z].name;
            j++;
            z++;
            first--;
        }
        z=0;
        while (second >0){
            tab[j].rate = bucket[1][z].rate;
            tab[j].name = bucket[1][z].name;
            j++;
            z++;
            second--;
        }
        z=0;
        while (third >0){
            tab[j].rate = bucket[2][z].rate;
            tab[j].name = bucket[2][z].name;
            j++;
            z++;
            third--;
        }
        z=0;
        while (fourth >0){
            tab[j].rate = bucket[3][z].rate;
            tab[j].name = bucket[3][z].name;
            j++;
            z++;
            fourth--;
        }
        z=0;
        while (fifth >0){
            tab[j].rate = bucket[4][z].rate;
            tab[j].name = bucket[4][z].name;
            j++;
            z++;
            fifth--;
        }
    
    //free array memory
    delete[] bucket[0];
    delete[] bucket[1];
    delete[] bucket[2];
    delete[] bucket[3];
    delete[] bucket[4];
    delete[] bucket;
};

//function to create a file with no empty grades
//used only once
void create_file(){
    string tmp;
    ifstream MyReadfile("projekt2_dane.csv");
    ofstream newplik("dane.txt");
    while(getline(MyReadfile, tmp)){
        if (tmp[tmp.length()-1] == '0'){
            newplik << tmp <<endl;    
        }
    }
    newplik.close();
    MyReadfile.close();
}

//function to create an array with movies and their ratings from the txt file obtained with the create file function
// the size argument is the size of the array we want to create
movie* create_table(int size){
    string tmp;
    ifstream MyReadFile("dane.txt");
    movie* tab = new movie[size];

    if (!MyReadFile.is_open()){
        cout<<"File open error\n";
        delete[] tab;
        exit(0);
    }
    else{
        for (int i = 0; i<size; i++){
            getline(MyReadFile, tmp);
            char buffer[1000];
            int length_n = tmp.length();
            size_t length = tmp.copy(buffer, 4, length_n - 4);
            buffer[length] = '\0';

            tmp.erase(length_n-4, length);

            if (buffer[0] == ','){
                char tmp_buffer[4];
                for(int i = 0; i<3; i++){
                    tmp_buffer[i]=buffer[i+1];
                }
            tmp_buffer[3]='\0';
            float rate = atof(tmp_buffer);
            tab[i].name = tmp;
            tab[i].rate = rate;
            }
            else{
                float ratio1 = atof(buffer);
                tab[i].name = tmp;
                tab[i].rate = ratio1;
            }
        }
        return tab;
    }
}

int main()
{
int size_of;
while(1){
    cout<<"Enter the number of data to be sorted \n MAX: 962902; Exit the program - enter 0 \n Number of data to be sorted:";
    cin>>size_of;
    if(size_of<=0||size_of>=962902){
        break;
    }
    else{
//    create_file();
    movie* table = new movie[7];
    table[0].name='a';table[0].rate=6;
    table[1].name='a';table[1].rate=2;
    table[2].name='a';table[2].rate=2;
    table[3].name='a';table[3].rate=4;
    table[4].name='a';table[4].rate=8;
    table[5].name='a';table[5].rate=10;
    table[6].name='a';table[6].rate=9;
    movie* table1 = create_table(size_of);
    movie* table2 = create_table(size_of);
    movie* table3 = create_table(size_of);

    // for(int i =0; i <size_of; i++){
    //    cout<<table1[i].name<<" rate:"<<table1[i].rate<<endl;
    // }

    //-----------QUICKSORT ALGORITHM-------------------------
    double time_start = (double)clock();

    quicksort(table1, 0, (size_of-1));
  
    double time_end = (double)clock();
    cout<<"Sorting by the quicksort algorithm took: "<<(time_end - time_start)/(CLOCKS_PER_SEC)<<" seconds. \n"<<endl;
    delete[] table1;
    
    //-------------BUCKETSORT ALGORITHM-----------------------
    time_start = (double)clock();

    bucket_sort(table2, size_of);
    
    time_end = (double)clock();
    cout<<"The sorting algorithm took: "<<(time_end - time_start)/(CLOCKS_PER_SEC)<<" seconds. \n"<<endl;
    delete[] table2;

    //------------MERGE SORT ALGORITHM--------------------------
    time_start = (double)clock();

    divaid_mgs(table3, 0, size_of-1);

    time_end = (double)clock();
    cout<<"The mergesort algorithm was sorted by: "<<(time_end - time_start)/(CLOCKS_PER_SEC)<<" seconds. \n"<<endl;
    delete[] table3;
    }
}
    return 0;
};