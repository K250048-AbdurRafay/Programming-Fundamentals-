#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

// ---------------- BACKEND ----------------

// Understand It 
void store_in_file(char text[]){
    FILE *fptr;
    fptr = fopen("expenses.txt", "a");
    if(!fptr){printf("Error opening file\n");}
    fprintf(fptr, "%s\n", text);
    fclose(fptr);
}

// UNDERSTAND IT
char* generate_line(char line[], char return_line[], int *cost){
    char expense[15] = "\0";
    int found  = 0;
    char reason[64] = "\0";

    for (int i = 0; i < strlen(line); i++)
    {
        char temp[2];
        temp[0] = line[i];
        temp[1] = '\0';

        if (line[i] == '_')
        {
            found = 1;
        }
        else if (found)
        {
            strcat(reason, temp);
        }
        else{
            strcat(expense, temp);
        }
    }

    (*cost) = atoi(expense);
    strcat(return_line, expense);
    strcat(return_line, "  ----------  ");
    strcat(return_line, reason);
    return return_line;
}

// UNDERSTAND IT 
void generate_report(int budget){
    FILE *fptr;
    char return_line[64] = "\0";
    char report_line[64] = "\0";
    int cost = 0, total = 0;

    char line[64];
    fptr = fopen("expenses.txt", "r");

    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        return_line[0] = '\0';
        strcpy(report_line, generate_line(line, return_line, &cost)); 
        total += cost;
        printf("%s\n", report_line);
    }

    fclose(fptr);

    printf("Total Expense : %d\n", total);

    if (total >= budget)
    {
        printf("\n\nSUGGESTION : Your expenses are going beyond your budget, try to cut down some expenses.\n");
    }
    else{
        printf("SUGGESTION: Your expenses are under budget. Keep it up\n\n");
    }

    printf("\n--- end of report ---\n");
}

void take_input(char input[]){
    char input_cost[10] = "\0", input_reason[50] = "\0";

    printf("\nEnter expense made: ");
    scanf("%s", input_cost);
    getchar();

    printf("Enter reason for expense: ");
    fgets(input_reason, sizeof(input_reason), stdin);

    input_reason[strcspn(input_reason, "\n")] = '\0';  // remove \n

    strcpy(input, input_cost);
    strcat(input, "_");
    strcat(input, input_reason);
}


// UNDERSTAND IT 
void clear_all_data(){
    FILE *fptr;
    fptr = fopen("expenses.txt", "w");
    fclose(fptr);
}
// ---------------- END  of BACKEND ----------------


// ---------------- GUI   ----------------
#define WIN_W 1200
#define WIN_H 520

static int SmallButton(Rectangle r, const char *label){
    Vector2 m={(float)GetMouseX(),(float)GetMouseY()};
    Color fill = CheckCollisionPointRec(m,r) ? (Color){95,135,255,255} : (Color){80,120,235,255};
    DrawRectangleRec(r, fill);
    DrawRectangleLines((int)r.x,(int)r.y,(int)r.width,(int)r.height,(Color){28,28,70,255});
    int tw=MeasureText(label,16);
    DrawText(label,(int)(r.x+(r.width-tw)/2),(int)(r.y+r.height/2-8),16,RAYWHITE);
    return IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(m,r);
}

// Build report + total
// UNDERSTAND IT 
static void BuildReport(char *out,int outsize,int *outTotal){
    FILE *f = fopen("expenses.txt","r");
    if (!f) { 
        snprintf(out, outsize, "No expenses yet.\n"); 
        *outTotal = 0; 
        return; 
    }
    char line[128], ret[128], rpt[128];
    int cost, total = 0;
    out[0] = 0;

    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;  
        ret[0] = 0;
        strcpy(rpt, generate_line(line, ret, &cost));
        total += cost;
        strncat(out, rpt, outsize - strlen(out) - 1);
        strncat(out, "\n", outsize - strlen(out) - 1);
    }

    fclose(f);
    *outTotal = total;
}


int main(void){
    InitWindow(WIN_W,WIN_H,"Budget Tracker - Minimal");
    SetTargetFPS(60);

    char salary[32]="", savings[32]="", expense_name[64]="", expense_amt[32]="", input_buf[128]="";
    int active=0;

    
    int left_x=20, spacing=60; 
    Rectangle rSalary={left_x,20,200,30}, rSavings={left_x,20+spacing,200,30};
    Rectangle rExpName={left_x,20+2*spacing,200,30}, rExpAmt={left_x,20+3*spacing,200,30};
    Rectangle rAdd={left_x,20+4*spacing,100,30}, rClear={left_x+120,20+4*spacing,100,30};
    Rectangle rReport={240,20,WIN_W-260,WIN_H-40};

    char report_buf[4096]; int report_total=0;
    BuildReport(report_buf,sizeof(report_buf),&report_total);

    while(!WindowShouldClose()){
       
        int key=GetCharPressed();
        while(key>0){
            if(key>=32 && key<=125){
                if(active==1 && strlen(salary)<sizeof(salary)-1) salary[strlen(salary)]=(char)key,salary[strlen(salary)+1]=0;
                if(active==2 && strlen(savings)<sizeof(savings)-1) savings[strlen(savings)]=(char)key,savings[strlen(savings)+1]=0;
                if(active==3 && strlen(expense_name)<sizeof(expense_name)-1) expense_name[strlen(expense_name)]=(char)key,expense_name[strlen(expense_name)+1]=0;
                if(active==4 && strlen(expense_amt)<sizeof(expense_amt)-1) expense_amt[strlen(expense_amt)]=(char)key,expense_amt[strlen(expense_amt)+1]=0;
            } key=GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACKSPACE)){
            if(active==1 && strlen(salary)>0) salary[strlen(salary)-1]=0;
            if(active==2 && strlen(savings)>0) savings[strlen(savings)-1]=0;
            if(active==3 && strlen(expense_name)>0) expense_name[strlen(expense_name)-1]=0;
            if(active==4 && strlen(expense_amt)>0) expense_amt[strlen(expense_amt)-1]=0;
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Vector2 m={(float)GetMouseX(),(float)GetMouseY()};
            if(CheckCollisionPointRec(m,rSalary)) active=1;
            else if(CheckCollisionPointRec(m,rSavings)) active=2;
            else if(CheckCollisionPointRec(m,rExpName)) active=3;
            else if(CheckCollisionPointRec(m,rExpAmt)) active=4;
            else active=0;
        }

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            if(SmallButton(rAdd,"Add")){
                input_buf[0]=0; strcpy(input_buf,expense_amt); strcat(input_buf,"_"); strcat(input_buf,expense_name);
                store_in_file(input_buf); expense_amt[0]=0; expense_name[0]=0;
                BuildReport(report_buf,sizeof(report_buf),&report_total);
            }
            if(SmallButton(rClear,"Clear All")){
                clear_all_data();
                BuildReport(report_buf,sizeof(report_buf),&report_total);
            }
        }

        
        BeginDrawing();
        ClearBackground((Color){245,248,255,255});

        
        DrawText("Salary:",left_x,rSalary.y-20,16,BLACK);
        DrawRectangleRec(rSalary,WHITE); DrawText(salary,(int)rSalary.x+8,(int)rSalary.y+5,16,BLACK);

        DrawText("Savings:",left_x,rSavings.y-20,16,BLACK);
        DrawRectangleRec(rSavings,WHITE); DrawText(savings,(int)rSavings.x+8,(int)rSavings.y+5,16,BLACK);

        DrawText("Expense Name:",left_x,rExpName.y-20,16,BLACK);
        DrawRectangleRec(rExpName,WHITE); DrawText(expense_name,(int)rExpName.x+8,(int)rExpName.y+5,16,BLACK);

        DrawText("Amount:",left_x,rExpAmt.y-20,16,BLACK);
        DrawRectangleRec(rExpAmt,WHITE); DrawText(expense_amt,(int)rExpAmt.x+8,(int)rExpAmt.y+5,16,BLACK);

        SmallButton(rAdd,"Add"); SmallButton(rClear,"Clear All");

        
        DrawRectangleRec(rReport,(Color){250,250,255,255}); 
        DrawRectangleLines((int)rReport.x,(int)rReport.y,(int)rReport.width,(int)rReport.height,(Color){190,190,220,255});
        DrawText("Report",(int)rReport.x+8,(int)rReport.y+8,18,BLACK);

        
        int y=(int)rReport.y+36; const char *p=report_buf; char linebuf[256];
        while(*p && y<=(int)(rReport.y+rReport.height-80)){
            int i=0; while(*p && *p!='\n' && i<sizeof(linebuf)-1) linebuf[i++]=*p++; linebuf[i]=0; if(*p=='\n') p++;
            DrawText(linebuf,(int)rReport.x+8,y,14,BLACK); y+=20;
        }

        
        const char *suggestion;
        int avail_money = atoi(salary) - atoi(savings);  //UNDERSTAND IT 

        if (report_total < avail_money) { // UNDERSTAND IT 
            suggestion = "SUGGESTION: Very good! Your expenses are under control.";
        } 
        else {
            suggestion = "SUGGESTION: Warning! Your expenses exceed available money, decrease them.";
        }

        
        DrawText(suggestion,(int)rReport.x+8,(int)(rReport.y+rReport.height-60),16,(Color){200,30,30,255});

        
        char tot[80]; snprintf(tot,sizeof(tot),"Total Expense: %d",report_total);
        DrawText(tot,(int)rReport.x+8,(int)(rReport.y+rReport.height-40),16,(Color){10,10,40,255});

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
