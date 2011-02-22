#ifndef __FSM__H_
#define __FSM__H_
#include <map>
#include "OgreFrameListener.h"
#include <OIS/OIS.h>
namespace NS_RUN
{
    class IState
    {
        private:
            int mStateId;
        public:
            IState( int stateId ){ mStateId = stateId; };
            virtual ~IState(){};
            virtual void SwitchIn() {};
            virtual void SwitchOut() {};
            virtual void Update(const Ogre::FrameEvent& evt) {};
            
            virtual bool keyPressed( const OIS::KeyEvent &arg ){ return false;}; 
            virtual bool keyReleased( const OIS::KeyEvent &arg ) {return false;};
            
            int GetStateId() { return mStateId;}
    };
    class Fsm
    {
        typedef std::map<int, IState*> MAP_STATE;
        public:
            IState * mCurState;
            MAP_STATE mMapStates;
        public:
            Fsm();
            ~Fsm();
            
            void AddState(IState* pState);
            void SwitchState(int toStateId);
            void Update( const Ogre::FrameEvent& evt);
            
            bool keyPressed( const OIS::KeyEvent &arg );
            bool keyReleased( const OIS::KeyEvent &arg );
    };
}// the end of namespace

#endif
