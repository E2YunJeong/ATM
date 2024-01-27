#include "header.h"
#include "administrator.h"
#include "user.h"

int main() {

    int x;

    do
    {
        MENU();
        scanf_s("%d", &x);//메뉴를 입력 받음 
        switch (x)
        {
        case 0://프로그램 종료
            printf("ATM기 프로그램이 종료됩니다.\n");
            break;
        case 1://계좌생성
            ACOUNT_MAKE();
            break;
        case 2://입금 
            DEPOSIT();
            break;
        case 3://출금 
            WITHDRAW();
            break;
        case 4://송금 
            SEND();
            break;
        case 5://잔액조회
            BALANCE_CHECK();
            break;
        case 6://비밀번호 변경
            PASSWORD_CHANGE();
            break;
        case 7://관리자메뉴
            PASSWORD_CHECK();
            break;
        default: //잘못된 수를 입력했을 때
            printf("0~7 사이의 수를 입력해주세요.\n");
            Sleep(1000);
            break;
        }
    } while (x != 0);

	return 0;
}