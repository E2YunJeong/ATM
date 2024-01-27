#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

typedef struct _account {
    char acc_name[20];
    char acc_bankname[20];
    int acc_number;
    char acc_account[20];
    char acc_pass[5];
    int acc_money;
    char acc_balance[20];
}Account;//계좌 구조체 

struct PASSWORD {
    char check[5]; // 현재 비밀번호 확인
    char new1[5]; //새 비밀번호
    char new2[5]; //새 비밀번호 확인
}; // 관리자 메뉴 비밀번호 구조체

struct BANKINFO {
    char bankname[256]; //은행 이름
    char username[256]; //계좌 주인 이름
    int balance; // 계좌 잔액
    char password[256]; //계좌 비밀번호
}; //은행 기본 정보

Account person[100], tmp;

int count = 0, i, j, toAccount;
Account fileinfo[100];
Account accountinfo[100];

void ACCOUNT_INFO(void);//계좌정보 파일 저장 함수
void MENU(void); //메인 메뉴 함수
int ACOUNT_MAKE(void); //계좌생성 함수
int DEPOSIT(void); //입금 함수
int WITHDRAW(void);//출금 함수
int SEND(void);//송금 함수
void BALANCE_CHECK(void);//잔액조회 함수
void PASSWORD_CHANGE(void);//비밀번호 변경 함수
void ACCOUNT_LOCK(char* acc);//계좌 정지 함수
int LOCK_CHECK(char* acc); //계좌 정지 상태 확인 함수
int ACCOUNT_CHECK(char* acc); //계좌 유무 확인 함수

void PASSWORD_CHECK(void); //관리자 메뉴 비밀번호 확인 함수
void SYSTEM_MENU(void); // 관리자 메뉴 함수
void BANKADD(void); //은행 추가 함수
void ACCOUNT_UNLOCK(void); //계좌 정지 해제 함수
void ATM_CHECK(void); //ATM 잔고 확인 함수
void ATM_ADD(void); //ATM 잔고 추가 함수
void SYSTEM_PASSWORD_CHANGE(void);// 관리자 비밀번호 변경 함수
