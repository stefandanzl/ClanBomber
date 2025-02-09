/* This file is part of ClanBomber <http://www.nongnu.org/clanbomber>.
 * Copyright (C) 1999-2004, 2007 Andreas Hundt, Denis Oliver Kropp
 * Copyright (C) 2008-2011, 2017 Rene Lopez <rsl@member.fsf.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ClanBomber.h"
#include "PlayerSetup.h"

#include "GameConfig.h"
#include "Timer.h"
#include "Controller.h"

#include "SDL_ttf.h"
#include "Utils.h"

#include <sstream>

PlayerSetup::PlayerSetup(ClanBomberApplication* _app)
{
	app = _app;
	cur_row = 0;
	cur_col = 0;
}

PlayerSetup::~PlayerSetup()
{
}

void PlayerSetup::exec()
{
	draw();
	///primary->Flip( primary, NULL, DSFLIP_WAITFORSYNC  );
	CB_Flip();

	///DFBInputEvent 

	SDL_Event event;

	///keybuffer->Reset(keybuffer);
	
	while (1) {
	  //keybuffer->WaitForEvent( keybuffer );
		SDL_PumpEvents();
		if(SDL_WaitEvent(&event)) {
		  if(event.type != SDL_KEYDOWN) {
		    continue;
		  }
		}
				
		/**if (keybuffer->GetEvent( keybuffer, DFB_EVENT(&event) ) == DFB_OK) {
			if (event.type != DIET_KEYPRESS ) {
				continue;
			}
			}	**/
	
		///switch (DFB_LOWER_CASE(event.key_symbol)) {
		switch (event.key.keysym.sym) {
		case SDLK_BACKSPACE:
		case SDLK_ESCAPE:
		  return;
		  break;
		  //case DIKS_OK:
		case SDLK_RETURN:
		  Resources::Menu_clear()->play();
		  handle_enter();
		  GameConfig::save();
		  break;
		case SDLK_SPACE:
		  if (GameConfig::bomber[cur_row].is_enabled()) {
					GameConfig::bomber[cur_row].disable();
		  }
		  else {
		    GameConfig::bomber[cur_row].enable();
		  }
		  GameConfig::save();
		  Resources::Menu_clear()->play();
		  break;
		case SDLK_h:
		  GameConfig::bomber[cur_row].set_highlight_maptile(!GameConfig::bomber[cur_row].get_highlight_maptile());
		  GameConfig::save();
		  Resources::Menu_clear()->play();
		  break;
		case SDLK_DOWN:
		  cur_row += (cur_row<7) ? 1 : 0;
		  Resources::Menu_break()->play();
		  break;
		case SDLK_UP:
		  cur_row -= (cur_row>0) ? 1 : 0;
		  Resources::Menu_break()->play();
		  break;
		case SDLK_LEFT:
		  cur_col -= (cur_col>0) ? 1 : 0;
		  Resources::Menu_break()->play();
		  break;
		case SDLK_RIGHT:
		  cur_col += (cur_col<3) ? 1 : 0;
		  Resources::Menu_break()->play();
		  break;
		}
	
		draw();
		//primary->Flip( primary, NULL, DSFLIP_WAITFORSYNC  );
		CB_Flip();
       }
}

void PlayerSetup::draw(bool fick)
{
        int cg[5] = { 17, 95, 340, 500, 720 };

	///primary->SetBlittingFlags( primary, DSBLIT_NOFX );
	///primary->Blit( primary, Resources::Playersetup_background(), NULL, 0, 0 );
	Resources::Playersetup_background()->blit(0, 0);
	
	///primary->SetFont( primary, Resources::Font_small() );	
	///primary->SetColor( primary, 0xFF, 0xFF, 0xFF, 0xFF );
	///primary->DrawString( primary, "SKIN", -1, 55, 40, DSTF_CENTER);
	Resources::Font_small()->render(_("SKIN"), 55, 40,
                                        cbe::FontAlignment_0center);
	///primary->DrawString( primary, "NAME", -1, 130, 40, DSTF_CENTER);
	Resources::Font_small()->render(_("NAME"), 130, 40,
                                        cbe::FontAlignment_0center);
	///primary->DrawString( primary, "TEAM", -1, 418, 40, DSTF_CENTER);
	Resources::Font_small()->render(_("TEAM"), 418, 40,
                                        cbe::FontAlignment_0center);
	///primary->DrawString( primary, "CONTROLLER", -1, 612, 40, DSTF_CENTER);
	Resources::Font_small()->render(_("Controller"), 612, 40,
                                        cbe::FontAlignment_0center);

	///primary->DrawString( primary, "SPACE ENABLES OR DISABLES A PLAYER, H TOGGLES HIGHLIGHTING", -1, 12, 580, DSTF_TOPLEFT);
	Resources::Font_small()->render(_("SPACE ENABLES OR DISABLES A PLAYER, "
                                          "H TOGGLES HIGHLIGHTING"), 12, 580,
                                        cbe::FontAlignment_0topleft);
		
	///primary->SetColor( primary, 55, 110, 220, 70 );
	///primary->SetDrawingFlags( primary, DSDRAW_BLEND );
	///primary->FillRectangle( primary, 0, 70+cur_row*63, 800, 63 );
	CB_FillRect(0, 70+cur_row*63, 800, 63, 55, 110, 220, 70);
	
	if (!fick) {
	  ///primary->SetColor( primary, 40, 40, 240, 120 );
	  ///primary->FillRectangle( primary, cg[cur_col], 70+cur_row*63, cg[cur_col+1] - cg[cur_col], 63 );
	  CB_FillRect(cg[cur_col], 70+cur_row*63, cg[cur_col+1] - cg[cur_col], 63, 40, 40, 240, 120);
	}

	for (int i=0; i<8; i++) {
		if (GameConfig::bomber[i].get_highlight_maptile()) {
		  ///primary->SetColor( primary, 0x00, 0x00, 0xFF, 50 );
		  ///primary->FillRectangle( primary, 34, 90+i*63, 40, 40 );
		  CB_FillRect(34, 90+i*63, 40, 40, 0x00, 0x00, 0xFF, 50);
		}
		
		Resources::Bombers(GameConfig::bomber[i].get_skin())->blit(35, 130+i*63 - Resources::Bombers(GameConfig::bomber[i].get_skin())->getHeight(), 0);

                cbe::Font *font = Resources::Font_small();
		if (!fick || cur_row != i) {
		  font = Resources::Font_big();
		}
		///primary->SetColor( primary, 0x20, 0x90, 0xF0, 0xFF );
		///primary->DrawString( primary, GameConfig::bomber[i].get_name(), -1, 130, 90 + i*63, DSTF_TOPLEFT );
		font->render(GameConfig::bomber[i].get_name(), 130, 90 + i*63,
                             cbe::FontAlignment_0topleft);
		
		Resources::Playersetup_teams()->blit( 360, 72 + i*63, GameConfig::bomber[i].get_team() );

		
		///primary->SetFont( primary, Resources::Font_small() );
		///primary->SetColor( primary, 0xFF, 0xFF, 0xFF, 0xFF );
		switch ( GameConfig::bomber[i].get_controller() ) {
			case Controller::AI:
				Resources::Playersetup_controls()->blit( 550, 72 + i*63,0);
				///primary->DrawString( primary, "DOK", -1, 650, 102 + i*63, DSTF_TOPRIGHT );
				Resources::Font_small()->render("DOK", 650,
                                                                102 + i*63,
                                                                cbe::FontAlignment_0topright);
				break;
			case Controller::AI_mass:
				Resources::Playersetup_controls()->blit( 550, 72 + i*63,0);
				///primary->DrawString( primary, "MASS", -1, 650, 102 + i*63, DSTF_TOPRIGHT );
				Resources::Font_small()->render("MASS", 650,
                                                                102 + i*63,
                                                                cbe::FontAlignment_0topright);
				break;
			case Controller::KEYMAP_1:
			case Controller::KEYMAP_2:
			case Controller::KEYMAP_3:
				Resources::Playersetup_controls()->blit( 550, 72 + i*63,GameConfig::bomber[i].get_controller()-Controller::KEYMAP_1+1);
				break;
                case Controller::RCMOUSE:
                  Resources::Font_small()->render("RCMOUSE", 612, 110 + i*63,
                                                  cbe::FontAlignment_0center);
                  break;
			case Controller::JOYSTICK_1:
			case Controller::JOYSTICK_2:
			case Controller::JOYSTICK_3:
			case Controller::JOYSTICK_4:
			case Controller::JOYSTICK_5:
			case Controller::JOYSTICK_6:
			case Controller::JOYSTICK_7:
				Resources::Playersetup_controls()->blit( 550, 72 + i*63,4);
                                std::stringstream number;
                                number << GameConfig::bomber[i].get_controller()-Controller::JOYSTICK_1+1;
                                Resources::Font_small()->render(number.str(),
                                                                620,
                                                                70 + i*63,
                                                                cbe::FontAlignment_0topleft);
				Resources::Font_small()->render(SDL_JoystickName(GameConfig::bomber[i].get_controller() - Controller::JOYSTICK_1),
                                                                500,
                                                                132 + i*63);
				break;
		}

		if (!GameConfig::bomber[i].is_enabled()) {
		  ///primary->SetColor( primary, 0, 0, 0, 170 );
		  ///primary->SetDrawingFlags( primary, DSDRAW_BLEND );
		  ///primary->FillRectangle( primary, 0, 70+i*63, 800, 63 );
		  CB_FillRect(0, 70+i*63, 800, 63, 0, 0, 0, 170);
		}
       }
}

void PlayerSetup::handle_enter()
{
  switch (cur_col) {
  case 0:
    GameConfig::bomber[cur_row].set_skin( GameConfig::bomber[cur_row].get_skin()+1 );
    break;
  case 1:
    enter_name(); Resources::Menu_clear()->play();
    break;
  case 2:
    GameConfig::bomber[cur_row].set_team( GameConfig::bomber[cur_row].get_team()+1 );
    break;
  case 3:
    GameConfig::bomber[cur_row].set_controller( GameConfig::bomber[cur_row].get_controller()+1 );
    break;
  }
}

void PlayerSetup::enter_name()
{
        float alpha = 0;
			
	///keybuffer->Reset( keybuffer );
	std::string new_string = GameConfig::bomber[cur_row].get_name();
	
	Timer::reset();
	
	///primary->SetDrawingFlags( primary, DSDRAW_BLEND );
	while (1) {
		alpha += Timer::time_elapsed(true);
		while (alpha > 0.5f) {
			alpha -= 0.5f;
		}
		draw(true);
		///primary->SetColor( primary, 50, 220, 128, (alpha>0.25f) ? (unsigned char)((0.5f-alpha)*3.0f*255) : (unsigned char)(alpha*3.0f*255) );
		///primary->FillRectangle( primary, 95, 70+cur_row*63, 245, 63 );
		CB_FillRect(95, 70+cur_row*63, 245, 63, 50, 220, 128, (alpha>0.25f) ? (Uint8)((0.5f-alpha)*3.0f*255) : (Uint8)(alpha*3.0f*255));
		///primary->SetFont( primary, Resources::Font_big() );
		///primary->SetColor( primary, 0xFF, 0xFF, 0xFF, 0xFF );
		///primary->DrawString( primary, new_string, -1, 130, 90 + cur_row*63, DSTF_TOPLEFT);		
		Resources::Font_big()->render(new_string, 130, 90 + cur_row,
                                              cbe::FontAlignment_0topleft);

		///primary->Flip( primary, NULL, DSFLIP_WAITFORSYNC  );
		CB_Flip();
		
		
		if (CB_EnterText(new_string)) {
			GameConfig::bomber[cur_row].set_name( new_string );
			return;
		}		
       }
}
