#pragma once
#include "header.h"

void PASSWORD_CHECK(void) {
    struct BANKINFO B;
    FILE* atm;
    char buffer[256];
    char check[256];
    int END = 0;

    if ((atm = fopen("atm.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);

    do {
        printf("비밀번호를 입력하세요 : ");
        scanf("%s", check);
        printf("\n");

        if (strcmp(check, B.password) == 0) {
            SYSTEM_MENU();
            return 0;
            END = 1;
        }
        else {
            printf("\n비밀번호가 일치하지 않습니다. 다시 입력해주세요.\n");
        }
    } while (END != 1);

    fclose(atm);
}//비밀번호 확인 함수

void SYSTEM_MENU(void) {
    int choice; //메뉴 선택 변수

    do {
        system("cls");

        printf("=======관리자 메뉴=======\n");
        printf("1. 은행 추가\n2. 계좌 정지 해제\n3. ATM잔고 확인\n4. ATM잔고 보충\n5. 관리자 비밀번호 변경\n0. 메인메뉴\n");
        printf("=========================\n>> ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 0: //메인메뉴
            printf("메인메뉴로 돌아갑니다.\n\n");
            Sleep(2000);
            break;
        case 1: //은행 추가
            BANKADD();
            break;
        case 2: //계좌 정지 해제
            ACCOUNT_UNLOCK();
            break;
        case 3: //ATM잔고 확인
            ATM_CHECK();
            break;
        case 4: //ATM잔고 보충
            ATM_ADD();
            break;
        case 5: //관리자 비밀번호 변경
            SYSTEM_PASSWORD_CHANGE();
            break;
        default: //잘못된 수를 입력했을 때
            printf("0~5 사이의 수를 입력해주세요.\n");
            Sleep(1000);
            break;
        }
    } while (choice != 0);
}// 관리자 메뉴 함수

void BANKADD(void) {
    system("cls");

    FILE* bank;
    char bank_add[256];

    if ((bank = fopen("은행.txt", "a")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    printf("추가할 은행을 입력해주세요 : ");
    scanf("%s", bank_add);

    fprintf(bank, "%s\n", bank_add);
    printf("%s이(가) 추가되었습니다.\n\n", bank_add);
    fclose(bank);
    Sleep(2000);
}// 은행 추가 함수

void ACCOUNT_UNLOCK(void) {
    system("cls");

    FILE* bank, * newfile;
    char buffer[256];
    char account[256];
    int count1 = 0, count2 = 0;

    if ((bank = fopen("은행.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    if ((newfile = fopen("은행2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    printf("정지를 해제할 계좌번호를 입력하세요 : ");
    scanf("%s", account);

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, account)) {
            if (strstr(buffer, "x")) {
                fprintf(newfile, "%s\n", account);
                printf("%s 계좌가 해제되었습니다.\n", account);
            }
            else {
                printf("해당 계좌는 정지 상태가 아닙니다.\n");
                fputs(buffer, newfile);
            }
        }
        else {
            fputs(buffer, newfile);
            count2++;
        }
        count1++;
    }
    if (count2 == count1) {
        printf("%s 계좌는 없는 계좌입니다.\n", account);
    }

    fclose(bank);
    fclose(newfile);

    remove("은행.txt");
    if (rename("은행2.txt", "은행.txt") != 0) {
        printf("이름 변경 실패\n");
    }
    Sleep(2000);
}// 계좌 정지 해제 함수

void ATM_CHECK(void) {
    system("cls");

    FILE* atm;
    char buffer[256];
    struct BANKINFO B;

    if ((atm = fopen("atm.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }
    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);
    printf("ATM의 현재 잔고는 %d원 입니다.\n", B.balance);

    fclose(atm);
    Sleep(2000);
}// ATM 잔고 확인 함수

void ATM_ADD(void) {
    system("cls");

    FILE* atm, * newfile;
    char buffer[256];
    int money;
    struct BANKINFO B;

    if ((atm = fopen("atm.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    if ((newfile = fopen("atm2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    fgets(buffer, 256, atm);

    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);
    printf("추가할 금액을 입력하세요 : ");
    scanf("%d", &money);
    B.balance += money;

    printf("ATM의 현재 잔고는 %d원 입니다.\n", B.balance);

    fputs(buffer, newfile);
    fprintf(newfile, "    %s   %s   %d       %s\n", B.bankname, B.username, B.balance, B.password);

    fclose(atm);
    fclose(newfile);

    remove("atm.txt");
    if (rename("atm2.txt", "atm.txt") != 0) {
        printf("이름 변경 실패\n");
    }
    Sleep(2000);
}//ATM 잔고 추가 함수

void SYSTEM_PASSWORD_CHANGE() {
    system("cls");

    struct PASSWORD P;
    struct BANKINFO B;
    FILE* atm, * newfile;
    char buffer[256];
    int END = 0;

    if ((atm = fopen("atm.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    if ((newfile = fopen("atm2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);

    do {
        printf("현재 비밀번호를 입력해주세요 : ");
        scanf("%s", P.check);

        //현재 비밀번호 일치
        if (strcmp(B.password, P.check) == 0) {
            while (END != 1) {
                printf("\n새 비밀번호를 입력해주세요 (4자리 숫자) : ");
                scanf("%s", P.new1);
                printf("새 비밀번호를 다시 입력해주세요 (4자리 숫자) : ");
                scanf("%s", P.new2);

                //새 비밀번호의 자리수가 4자리가 아닐 때
                if (strlen(P.new1) != 4) {
                    printf("\n비밀번호 형식이 맞지 않습니다. 다시 입력해주세요.\n");
                }
                else {
                    //새 비밀번호 일치
                    if (strcmp(P.new1, P.new2) == 0) {
                        fputs(buffer, newfile);
                        fprintf(newfile, "    %s   %s   %d       %s\n", B.bankname, B.username, B.balance, P.new1);
                        printf("\n비밀번호가 변경되었습니다.\n");
                        END = 1;
                    }

                    //새 비밀번호 불일치
                    else {
                        printf("\n비밀번호가 일치하지 않습니다. 다시 입력해주세요.\n");
                    }
                }
            }
        }
        //현재 비밀번호 불일치
        else {
            printf("\n비밀번호가 일치하지 않습니다. 다시 입력해주세요.\n\n");
        }
    } while (END != 1);

    fclose(atm);
    fclose(newfile);

    remove("atm.txt");
    if (rename("atm2.txt", "atm.txt") != 0) {
        printf("이름 변경 실패\n");
    }
    Sleep(2000);
} //관리자 비밀번호 변경 함수
