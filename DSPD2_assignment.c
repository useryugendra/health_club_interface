#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct member
{
    int member_id;
    char name[20];
    int age;
    char gender[7];
    char program[20];
    int fee_paid;
    struct member* next;
};
struct member* member_head=NULL;

struct trainer
{
    int trainer_id;
    char name[20];
    char can_train[20];
    int remuneration;
    int count;
    struct trainer* next;
};
struct trainer* trainer_head=NULL;
int trainer_count=0;
int member_count=0;
struct member* member_arr[15][5];
struct trainer* trainer_arr[15][5];

struct member* add_member(char name[20], int age, char gender[7], char program[20], int fee_paid)
{
    struct member* nptr=(struct member*)malloc(sizeof(struct member));
    static int i=1;
    nptr->age=age;
    strcpy(nptr->gender,gender);
    strcpy(nptr->program,program);
    strcpy(nptr->name,name);
    nptr->fee_paid=fee_paid;
    nptr->next=NULL;
    if(member_head==NULL)
    {
        member_head=nptr;
        nptr->member_id=1000+i;
    }
    else
    {
        struct member* temp;
        temp=member_head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=nptr;
        nptr->member_id=1000+i;
    }
    i++;
    member_count++;
    return member_head;
}

void add_trainer(char name[20], char program[20], int remuneration)
{
    struct trainer* nptr = (struct trainer*)malloc(sizeof(struct trainer));
    static int j=1;
    strcpy(nptr->name,name);
    strcpy(nptr->can_train,program);
    nptr->remuneration=remuneration;
    nptr->count=0;
    nptr->next=NULL;
    if(trainer_head==NULL)
    {
        trainer_head=nptr;
        nptr->trainer_id=1000+j;
    }
    else
    {
        struct trainer* temp=trainer_head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=nptr;
        nptr->trainer_id=1000+j;
    }
    j++;
}

void delete_member(int id)
{
    struct member* temp=member_head;
    struct member* temp1;
    int found=0;
    while(temp->next!=NULL && found==0)
    {
        temp1=temp->next;
        if(temp==member_head)
        {
            if(temp->member_id==id)
            {
                member_head=temp1;
                free(temp);
                found=1;
            }
            if(temp1->member_id==id)
            {
                temp->next=temp1->next;
                free(temp1);
                found=1;
            }
        }
        else if(temp1->member_id==id && found==0)
        {
            temp->next=temp1->next;
            free(temp1);
            found=1;
        }
    }
    if(temp1==NULL)
    {
        printf("there is no member with mentioned id..\n");
    }
    if(found==1)
    {
        printf("the member is sucessfully deleted...\n");
    }
}

void delete_trianer(int id)
{
    struct trainer* temp=trainer_head;
    struct trainer* temp1;
    int found=0;
    while(temp->next!=NULL && found==0)
    {
        temp1=temp->next;
        if(temp==trainer_head)
        {
            if(temp->trainer_id==id)
            {
                trainer_head=temp1;
                free(temp);
                found=1;
            }
            if(temp1->trainer_id==id)
            {
                temp->next=temp1->next;
                free(temp1);
                found=1;
            }
        }
        else if(temp1->trainer_id==id && found==0)
        {
            temp->next=temp1->next;
            free(temp1);
            found=1;
        }
    }
    if(temp1==NULL)
    {
        printf("there is no trainer with mentioned id..\n");
    }
    if(found==1)
    {
        printf("the trainer is sucessfully deleted...\n");
    }
}

void search_member(int id)
{
    struct member* temp=member_head;
    while(temp!=NULL)
    {
        if(temp->member_id==id)
        {
            printf("the name of the trainer is %s.\n",temp->name);
            printf("the age of the member is %d.\n",temp->age);
            printf("the gender of the member is %s.\n",temp->gender);
            printf("the program opted program by the member is %s",temp->program);
        }
        temp=temp->next;
    }
}

void search_trainer(int id)
{
    struct trainer* temp=trainer_head;
    while(temp!=NULL)
    {
        if(temp->trainer_id==id)
        {
            printf("the name of the trainer is %s.\n",temp->name);
            printf("the program that can be trained by the trainer is %s.\n",temp->can_train);
        }
        temp=temp->next;
    }
}

void print_member_list()
{
    struct member* temp=member_head;
    printf("id\tName\tGender\tAge\tProgram\n");
    printf("==============================================================\n");
    while(temp!=NULL)
    {
        printf("%d\t%s\t%s\t%d\t%s\n",temp->member_id,temp->name,temp->gender,temp->age,temp->program);
        temp=temp->next;
    }
}

void print_trainer_list()
{
    struct trainer* temp=trainer_head;
    printf("id\tName\tProgram\n");
    printf("==============================================================\n");
    while(temp!=NULL)
    {
        printf("%d\t%s\t%s\n",temp->trainer_id,temp->name,temp->can_train);
        temp=temp->next;
    }
}

void initialize_trainer_slots()
{
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<5;j++)
        {
            trainer_arr[i][j]=NULL;
        }
    }
}
void initialize_member_slots()
{
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<5;j++)
        {
            member_arr[i][j]=NULL;
        }
    }
}
/*  in the below function a 2-D array of address of the member nodes is passed and the size is [15]][5].15 represents 15 slots from 6am to 9pm, and the 5 represents the 
number of members in the gym in the particular slot. only 5 members because of the covid norms, so 5 will be members and the 5 will be trainers so total 10     */
void schedule_slot(struct member* ptr, int slot)
{
    for(int i=0;i<5;i++)
    {
        if(member_arr[slot][i]==NULL)
        {
            member_arr[slot][i]=ptr;
            break;
        }
        if(i==4)
        {
            printf("the gym is full for this slot...\n");
            schedule_slot(ptr,slot+1);
            break;
        }

    }
    struct trainer* temp=trainer_head;
    while(temp!=NULL)
    {
        if(strcmp(temp->can_train,ptr->program)==0)
        {
            for(int i=0;i<5;i++)
            {
                if(trainer_arr[slot][i]==NULL)
                {
                    trainer_arr[slot][i]=temp;
                    break;
                }
                if(trainer_arr[slot][i]==temp)
                {
                    printf("the trainer is already assigned to this slot...\n");
                    member_arr[slot][i]=NULL;
                    schedule_slot(ptr,slot+1);
                    break;
                }
                if(i==4)
                {
                    printf("the gym is full for this slot...\n");
                    schedule_slot(ptr,slot+1);
                    break;
                }
            }
        }
        temp=temp->next;
    }

}

void print_hour_wise_list()
{
    printf("hour\tmember/trainer\tmember/trainer\tmember/trainer\tmember/trainer\tmember/trainer\n");
    for(int i=0;i<15;i++)
    {
        printf("%d-%d\t",i+6,i+7);
        for(int j=0;j<5;j++)
        {
            if(member_arr[i][j]!=NULL)
            {
                printf("%s/%s\t",member_arr[i][j]->name,trainer_arr[i][j]->name);
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}
void remuneration()
{
    int count=0;
    struct trainer* temp=trainer_head;
    while(temp!=NULL)
    {
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<5;j++)
            {
                if(trainer_arr[i][j]==temp)
                {
                    count++;
                }
            }
        }
        temp->remuneration=count*temp->remuneration;
        count=0;
        temp=temp->next;
    }
}

void sorted_remuneration_list()
{
     struct trainer* current = trainer_head;
     struct trainer* index = NULL;  
     int temp;  
          
        if(trainer_head == NULL)
        {  
            return;  
        }  
        else 
        {  
            while(current != NULL) 
            { 
                index = current->next;  
                  
                while(index != NULL) 
                {
                    if(current->remuneration < index->remuneration) 
                    {  
                        temp = current->remuneration;  
                        current->remuneration = index->remuneration;  
                        index->remuneration = temp;  
                    }  
                    index = index->next;  
                }  
                current = current->next;  
            }      
        }  
}

int main()
{
    initialize_member_slots();
    initialize_trainer_slots();
    int choice;
    printf("to add new member press 1...\nto add new trainer press 2...\nto schedule a slot press 3...\nto print hour wise list press 4...\nto delete member press 5...\n");
    printf("to delete trainer press 6...\nto search member press 7...\nto search trainer press 8...\nto print member list press 9...\nto print trianer list press 10...\n");
    printf("to print sorted remuneration list press 11...\nenter any other key to exit...\n");
    int flag=0;
    while(flag==0)
    {
        printf("enter your choice as demonstrated above: \n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: 
            {
                char name[20];
                char gender[7];
                char program[20];
                int age;
                int fee_paid;
                printf("enter name: \n");
                scanf("%s",name);
                printf("enter gender: \n");
                scanf("%s",gender);
                printf("enter age: \n");
                scanf("%d",&age);
                printf("please select any program Yoga, Cardio, Zumba and Weight lifting: \n");
                scanf("%s",program);
                printf("enter the fee: \n");
                scanf("%d",fee_paid);
                add_member(name,age,gender,program,fee_paid);
                break;
            }
            case 2: 
            {
                char name[20];
                char program[20];
                int remuneration;
                printf("enter name: \n");
                scanf("%s",name);
                printf("enter the program can be trained in the following Yoga, Cardio, Zumba and Weight lifting: \n");
                scanf("%s",program);
                printf("enter the remuneration: \n");
                scanf("%d",&remuneration);
                add_trainer(name,program,remuneration);
                break;
            }
            case 3:  
            {
                struct member* temp=member_head;
                int slot;
                int time;
                while(temp!=NULL)
                {
                    printf("enter the starting time you prefer in 24hr format from 6 to 21: \n");
                    scanf("%d",&time);
                    slot=time-6;
                    schedule_slot(temp,slot);
                    temp=temp->next;
                }
                break;
            }
            case 4: 
            {
                print_hour_wise_list();
                break;
            }
            case 5: 
            {
                int id;
                printf("enter the id to be deleted: \n");
                scanf("%d",&id);
                delete_member(id);
                break;
            }
            case 6: 
            {
                int id;
                printf("enter the id to be deleted: \n");
                scanf("%d",&id);
                delete_trianer(id);
                break;
            }
            case 7:
            {
                int id;
                printf("enter theid to be searched: \n");
                scanf("%d",&id);
                search_member(id);
                break;
            }
            case 8:
            {
                int id;
                printf("enter theid to be searched: \n");
                scanf("%d",&id);
                search_trainer(id);
                break;
            }
            case 9:
            {
                print_member_list();
                break;
            }
            case 10:
            {
                print_trainer_list();
                break;
            }
            case 11:
            {
                remuneration();
                sorted_remuneration_list();
                break;
            }
            default:
            {
                flag=1;
            }
        }
    }
    
}