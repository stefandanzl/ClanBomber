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

#ifndef DISEASE_H
#define DISEASE_H


class Bomber;
class Extra;

/**
 * Base for all diseases.
 * A disease is an negative effect given to a Bomber.
 * The disease are set manually before game start or are get by "touching" a
 * Extra of certain type while in game.
 * @todo Comment this and its derived right
 * @author Andreas Hundt
 * @author Denis Oliver Kropp
 * @see Extra
 */
class Disease
{
 public: 
  /**
   * Creates a Disease and attach it to a Bomber.
   * Creates a Disease and attach it to a {@link Bomber}.
   * @param _bomber Bomber which will get the disease.
   */
  Disease(Bomber* _bomber);
  /**
   * 
   */
  virtual ~Disease();
  /**
   *
   */	
  void act();
  /**
   *
   */
  float get_countdown() const;
  /**
   * Start the disease effects.
   */
  virtual void start()=0;
  /**
   * Stop the disease effects.
   */
  virtual void stop()=0;
  /**
   *
   */
  virtual Extra* spawn_extra(int _x, int _y)=0;	
  /**
   *
   */
  virtual Disease* spawn(Bomber* _bomber)=0;
  /**
   *
   */
  typedef enum
  {
    /**
     * Represents the Snail disease.
     */
    SLOW = -5,
    /**
     * Frozen.
     * Represents the Frozen disease.
     */
    FROZEN = -4,
    /**
     * Put Bomb
     */
    PUTBOMB = -3,
    /**
     * Stoned
     */
    STONED = -2,
    /**
     * Fast
     */
    FAST = -1,
  } DiseaseType;
  /**
   *
   */
  virtual DiseaseType get_DiseaseType()=0;
  /**
   *
   */
  static Disease* create(DiseaseType type, Bomber* _bomber);
 protected:
  Bomber* bomber;
  /**
   * Time that takes to the disease to terminate.
   * A positive float representing the number of seconds that the disease
   * will be in effect.
   */
  float countdown;
};

#endif
