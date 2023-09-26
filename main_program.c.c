#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void battle();

int main(void)
{
    battle();
    int program_ended;
    printf("Program ended! Press a number to close the cmd\n");
    scanf("%d", &program_ended);
    return 0;
}

void battle()
{
    int player_attack = 10;
    int player_health = 70;
    int enemy_attack = 30;
    int enemy_health = 100;
    bool battle_is_on = true;

    while(battle_is_on)
    {
        int input = 0;
        printf("Press a key to do damage!\n");
        scanf("%d", &input);

        enemy_health -= player_attack;
        if (enemy_health < 0)
        {
            enemy_health = 0;
        }
        printf("You dealt %d points of damage! The enemy's health is %d\n", player_attack, enemy_health);
        if (enemy_health == 0)
        {
            printf("Battle is over! You've won!\n");
            break;
        }

        printf("It's the enemy's turn, so he's going to do damage!\n");
        player_health -= enemy_attack;
        if (player_health < 0)
        {
            player_health = 0;
        }
        printf("The enemy dealt %d points of damage! Your health is %d\n", enemy_attack, player_health);
        if (player_health == 0)
        {
            printf("Battle is over! The enemy has won and you've lost!\n");
            break;
        }

        printf("======================= NEXT TURN! =======================  \n");
    }
}