# Minishell

[![Watch the video](https://img.youtube.com/vi/1LKCB-TarCw/hqdefault.jpg)](https://youtu.be/1LKCB-TarCw)

---

Project with [yochoi](https://github.com/AMATEURTOSS)

---

#### 프로그램 구조

1. [환경변수 처리](./srcs/utils/manage_list.c)

   처음엔 환경변수를 2차원 배열로만 관리하다가 shell의 export나 unset, PATH 등을 구현하려니 이차원 배열에서

   데이터의 추가나 삭제, 검색이 어려웠습니다.

   결국 환경변수를 딕셔너리로 키, 밸류 쌍으로 만들고 링크드리스트 형태로 추가나 제거, 탐색등이 쉽도록 구현하였습니다.

   

2. [시그널 처리](./srcs/handle_signal.c)

   Ctrl + c, d, \를 bash처럼 동작하도록 하는데,  각각 INTERUPT, EOF, QUIT 이

   아무것도 입력되지 않은 상태, 문자가 입력된 상태, blocking 상태에 따라서도 각각의 동작이 달라져서 어려움이 있었습니다.

   

3. [입력](./srcs/reader/read_line.c)

   double quote, simple quote가 나오는 경우 줄바꿈 문자까지 입력받도록 하기가 어려웠습니다.

   이를 위해서 quote가 열려있는지 닫혀있는지를 확인하고, escape 까지 확인하도록 구현하였습니다.

   

4. [문법 검사](./srcs/check_syntax.c)

   bash에선 lexer가 있는데, 여기선 간단하게 파이프기호나 리디렉션 기호들을 체크하면서 문법검사를 구현했습니다.

   

5. [파싱](./srcs/parser/parse_line.c)

   이 부분이 가장 어려웠습니다. 처음엔 리디렉션이나 파이프가 있는 명령을 C언어로 어떻게 실행하는지 조차 모르니, 파싱받을 구조체를 어떻게 설계하느냐부터 가장 어려웠습니다.

   혼자 예제코드를 보면서 가장 기본적인 리디렉션이나 파이프를 구현해보고 애쓰다가, 결국 다른분에게 여쭤보고 설명을 들으면서 코드를 참고하여 쉽게 해결 할 수 있었습니다.

   

6. [실행](./srcs/executer/execute_job.c)

   처음엔 fork와 exec함수를 이용하면서 프로세스를 이해하는데 힘들었고,

   나중엔 파이프가 연속적으로 오는 경우까지 고려해서 구현하는게 가장 어려웠는데, 파일 디스크립터에 대해서 찾아보고 많이 고민하던 와중에 팀원분이 stack overflow에 딱 알맞는 질문과 답변이 올라와있는 링크를 주셔서 해결했습니다.

   

7. [메모리 해제](./srcs/free.c)



---

참고

[mongshell](https://github.com/eunhyulkim/minishell) 

[fork_pipes](https://stackoverflow.com/questions/8082932/connecting-n-commands-with-pipes-in-a-shell)



---

