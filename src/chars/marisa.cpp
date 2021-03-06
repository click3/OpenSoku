#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "marisa.h"
#include <math.h>

char_marisa::char_marisa(inp_ab *func):
    char_c::char_c(func)
{
    viz.load_dat("marisa",0);
    char_loadsfx(this,"marisa");
};

char_marisa::char_marisa(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    viz.load_dat("marisa",pal);
    char_loadsfx(this,"marisa");
};


void char_marisa::stopping()
{
    if (field_49A)
    {
        if (h_inerc > 0)
        {
            h_inerc -= 0.5;
            if (h_inerc < 0)
            {
                reset_forces();
                field_49A = 0;
            }
        }
        if ( h_inerc < 0)
        {
            h_inerc += 0.5;
            if (h_inerc > 0)
            {
                reset_forces();
                field_49A = 0;
            }
        }
    }
    else
        reset_forces();
}

void char_marisa::stopping_posit(float p)
{
    if (field_49A)
    {
        h_inerc -= p;
        if (h_inerc < 0)
        {
            reset_forces();
            field_49A = 0;
        }
    }
    else
        reset_forces();
}

void char_marisa::func10()
{

    int32_t sq = get_seq();

    switch(sq)
    {
    case 0:
        sub10func(this);
        if (h_inerc == 0)
            field_49A = 0;
        stopping();
        viz.process();
        break;
    case 1:
        sub10func(this);
        stopping();
        if (viz.process() && viz.get_frame() == 0)
            set_seq(2);
        break;
    case 2:
        sub10func(this);
        stopping();
        viz.process();
        break;
    case 3:
        sub10func(this);
        stopping();
        if (viz.process() && viz.get_frame() == 0)
            set_seq(0);
        break;
    case 4:
        sub10func(this);
        char_h_move(this,6.0);
        viz.process();
        break;
    case 5:
        sub10func(this);
        char_h_move(this,-5.0);
        viz.process();
        break;
    case 6:
        if (viz.get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }

        if (viz.get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down(this))
            {
                set_seq(10);
                y = getlvl_height(this);
                reset_forces();
                break;
            }
        }

        viz.process();

        if (viz.get_subseq()       == 1 &&
                viz.get_frame_time()   == 0 &&
                viz.get_frame()        == 0 &&
                viz.get_elaps_frames() == 0)
        {
            v_inerc = 16.0;
            v_force = 0.75;
        }
        break;

    case 7:
        if (viz.get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }

        if (viz.get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down(this))
            {
                set_seq(10);
                y = getlvl_height(this);
                reset_forces();
                break;
            }
        }

        viz.process();

        if (viz.get_subseq()       == 1 &&
                viz.get_frame_time()   == 0 &&
                viz.get_frame()        == 0 &&
                viz.get_elaps_frames() == 0)
        {
            v_inerc = 16.0;
            v_force = 0.75;
            char_h_move(this, 5.0);
        }
        break;
    case 8:
        if (viz.get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }

        if (viz.get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down(this))
            {
                set_seq(10);
                y = getlvl_height(this);
                reset_forces();
                break;
            }
        }

        viz.process();

        if (viz.get_subseq()       == 1 &&
                viz.get_frame_time()   == 0 &&
                viz.get_frame()        == 0 &&
                viz.get_elaps_frames() == 0)
        {
            v_inerc = 16.0;
            v_force = 0.75;
            char_h_move(this, -4.0);
        }
        break;
    case 9:
        if (v_force == 0)
            v_force = 0.6;

        v_inerc -=v_force;

        if (char_on_ground_down(this))
        {
            set_seq(10);
            y = getlvl_height(this);
            reset_forces();
            break;
        }

        viz.process();
        break;
    case 10:
        sub10func(this);
        if (viz.process() && viz.get_frame() == 0)
            set_seq(0);
        break;

    case 300: //near A-attack
        sub10func(this);
        stopping_posit(0.5);

        if ( viz.process())
            set_seq(0);
        if ( viz.get_frame_time() == 0 && viz.get_frame() == 4 )
        {
            scene_play_sfx(27);
            field_49A = 0;
        }
        break;
    case 301: //far A-attack
        sub10func(this);
        stopping_posit(0.5);
        if (viz.get_frame() > 4 )
            stopping_posit(1.5);

        if ( viz.process() )
            set_seq(0);
        if ( viz.get_frame_time() == 0 )
        {
            if ( viz.get_frame() == 3 )
                h_inerc = 30.0;
            if ( viz.get_frame() == 4 )
            {
                h_inerc = 10.0;
                scene_play_sfx(27);
                field_49A = 0;
            }
        }
        if ( viz.get_frame() > 3 )
            stopping_posit(0.5);
        break;

    case 302: //6A(A)
    {
        uint32_t ssq = viz.get_subseq();
        if ( ssq == 0 || ssq == 1 || ssq == 4 )
            sub10func(this);

        if ( viz.get_frame() < 2 )
            if ( !input->keyDown(INP_A))
                not_charge_attack = 0;  // yeah, CHARGE

        if ( ssq == 0 )
            if ( h_inerc > 0)
                stopping_posit(0.75);

        if (viz.get_frame_time()   == 0 &&
                viz.get_frame()        == 0 &&
                viz.get_elaps_frames() == 0)
        {
            if (ssq == 2)
            {
                play_sfx(17);
                h_inerc = 15.5;
                v_inerc = 4.0;
                v_force = 0.55;
            }
            else if (ssq == 3)
            {
                play_sfx(17);
                h_inerc = 18.5;
                v_inerc = 7.5;
                v_force = 0.55;
            }
        }

        if ( viz.process() )
            set_seq(0);

        ssq = viz.get_subseq();
        uint32_t tf = viz.get_elaps_frames();

        if (viz.get_frame_time() == 0 &&
            viz.get_frame()      == 0 &&
                tf  == 0 &&
                ssq == 5)
            set_seq(0);

        if (ssq == 1)
        {
            if ( not_charge_attack == 0 && tf < 2 )
                next_subseq();
            else if ( tf > 12 )
                viz.set_subseq(3);
            else if ( tf == 2 ) // charge effect
            {
                //v241 = v3->rend_cls.y_pos + 68.0;
                //sub_438170(v3, 62, v3->rend_cls.x_pos, v241, v3->rend_cls.horizontal_direction, 1);
                scene_add_effect(62,x,y+68,dir);
            }
        }
        else if ( ssq == 3 || ssq == 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down(this) )
            {
                play_sfx(18);
                if ( ssq == 2 )
                    viz.set_subseq(4);
                else
                    viz.set_subseq(5);

                y = getlvl_height(this);
                v_inerc = 0.0;
                h_inerc = 5.0;
            }
        }
        else if ( ssq == 4 || ssq == 5 )
            stopping_posit(0.5);
    }
    break;


    case 521:
    {

        uint32_t sq = viz.get_subseq();

        if ( !sq || sq == 4 )
        {
            sub10func(this);
        }
        //field_18C = 1;
        if ( sq == 1 )
        {
            if ( viz.get_elaps_frames() > 20 )
            {
                viz.next_subseq();
            }
            /*if ( !(viz.get_elaps_frames() % 3) )
            {
              v1802 = (MT_getnext() % 60) + 95.0 - 30.0;
              v512 = get_MT_range(0x64u) * 0.1000000014901161;
              v1803 = v512 + 10.0;
              v1804 = (MT_getnext() & 3);
              v513 = v3->rend_cls.horizontal_direction;
              v514 = v3->rend_cls.y_pos + 51.0;
              v515 = v514;
              v516 = (40 * v513) + v3->rend_cls.x_pos;
              sub_46E2F0(v3, 810, v516, v515, v513, 1, &v1802, 3);
              v1 = 0.0;
            }*/
        }

        sq = viz.get_subseq();

        if ( sq > 0  && sq < 4 )
        {
            v_inerc -= 0.75;
            h_inerc -= 0.4;
            if ( h_inerc < 0)
                h_inerc = 0;
        }

        if ( sq == 3 && char_on_ground_down(this) )
        {
            viz.next_subseq();
            y = getlvl_height(this);
            reset_forces();
        }

        if ( viz.process() )
            set_seq(0);

        if (viz.get_subseq() == 1 && viz.get_frame_time()   == 0 &&
                viz.get_frame()  == 0 && viz.get_elaps_frames() == 0)
        {
            //v1661 = -85.0;
            //v1662 = 0.0;
            //v1663 = 1.0;
            //v519 = v3->rend_cls.y_pos + 232.0;
            //v520 = v519;
            //v521 = (61 * v3->rend_cls.horizontal_direction) + v3->rend_cls.x_pos;
            //sub_46E2F0(v3, 849, v521, v520, v3->rend_cls.horizontal_direction, 1, &v1661, 3);
            //sub_438170(v3, 127, v3->rend_cls.x_pos, v3->rend_cls.y_pos, v3->rend_cls.horizontal_direction, -1);
            play_sfx(5);
            //sub_479FF0(v3, 200, 120);
            //add_card_energy(v3, 50);
            h_inerc = 15.0;
            v_inerc = 25.0;
            v_force = 0.6;
        }

    }

    break;
    default:
        viz.process();
    }
}

void char_marisa::func20()
{
    if (char_on_ground(this))
    {
        {


            if (input->keyHit(INP_A) && input->gX(dir) == 0)
            {
                if (fabs(x - enemy->x) < 90)
                {
                    set_seq(300);
                }
                else
                {
                    set_seq(301);
                }

            }
            else if (input->keyHit(INP_A) && input->gX(dir) > 0)
            {
                set_seq(302);

            }
        }
    }

}


void char_marisa::set_seq_params()
{
    switch(viz.get_seq_id())
    {
    case 302:

        if ( !field_49A )
            reset_forces();
        //field_190 = 0;
        field_49A = 0;
        //field_194 = 1;
        not_charge_attack = 1;
        break;
    }
}
