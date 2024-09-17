#include "includeAll.h"

int main(int argc, const char *argv []){
        if(argc == 2){
                int level = atoi(argv[1]);
                switch(level){
                        case 1:
                                stageOne();
                                break;
                        case 2:
                                stageTwo();
                                break;
                        case 3:
                                stageThree();
                                break;
                        case 4:
                                stageFour();
                                break;
                        case 5:
                                stageFive();
                                break;
                        case 6:
                                stageSix();
                                break;
                        case 7:
                                stageSeven();
                                break;
                        case 8:
                                stageEight();
                                break;
                        case 9:
                                stageNine();
                                break;
                        case 10:
                                stageTen();
                                break;
                        default:
                                stageOne();
                }
        }else if(argc == 1){
                stageOne();
        }else{
                printf("Too many arguments");
        }
        return 0;
}
