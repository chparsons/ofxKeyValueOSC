#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class oscParamSenderAbstract
{
  public:
  oscParamSenderAbstract(){};
  virtual void send(){};
  virtual ofAbstractParameter& param(){};
};

template<typename T>
class oscParamSender : public oscParamSenderAbstract
{
  public:

    oscParamSender(){};
    ~oscParamSender()
    {
      _param.removeListener(this, &oscParamSender::update);
      sender = NULL;
    };

    ofParameter<T>& set( string name, T value, T min, T max  ) 
    {
      _param.set(name, value, min, max);
      return _param;
    };

    ofParameter<T>& set( string name, T value ) 
    {
      _param.set(name, value);
      return _param;
    };

    ofParameter<T>& init( ofxOscSender* sender ) 
    {
      this->sender = sender;
      _param.addListener(this, &oscParamSender::update);
      return _param;
    };

    virtual void send()
    {
      setup_msg();
      update_msg( _param.get() );
      sender->sendMessage(m);
    };

    virtual ofAbstractParameter& param() 
    {
      return _param;
    };

  private: 

    void update( T& value )
    {
      setup_msg();
      update_msg( value );
      sender->sendMessage(m);
    };

    void setup_msg()
    {
      m.clear();
      m.setAddress("/"+_param.getName());
    };

    void update_msg( float& value )
    { m.addFloatArg( value ); };

    void update_msg( double& value )
    { m.addFloatArg( value ); };

    void update_msg( int& value )
    { m.addIntArg( value ); };

    void update_msg( bool& value )
    { m.addIntArg( value ); };

    void update_msg( string& value )
    { m.addStringArg( value ); };

    void update_msg( ofVec2f& value )
    { 
      m.addFloatArg( value.x );
      m.addFloatArg( value.y );
    };

    void update_msg( ofVec3f& value )
    { 
      m.addFloatArg( value.x );
      m.addFloatArg( value.y );
      m.addFloatArg( value.z );
    };

    void update_msg( ofColor& value )
    { 
      m.addIntArg( value.r );
      m.addIntArg( value.g );
      m.addIntArg( value.b );
      m.addIntArg( value.a );
    };

    void update_msg( ofFloatColor& value )
    { 
      m.addFloatArg( value.r );
      m.addFloatArg( value.g );
      m.addFloatArg( value.b );
      m.addFloatArg( value.a );
    };


    void update_msg( const float& value )
    { m.addFloatArg( value ); };

    void update_msg( const double& value )
    { m.addFloatArg( value ); };

    void update_msg( const int& value )
    { m.addIntArg( value ); };

    void update_msg( const bool& value )
    { m.addIntArg( value ); };

    void update_msg( const string& value )
    { m.addStringArg( value ); };

    void update_msg( const ofVec2f& value )
    { 
      m.addFloatArg( value.x );
      m.addFloatArg( value.y );
    };

    void update_msg( const ofVec3f& value )
    { 
      m.addFloatArg( value.x );
      m.addFloatArg( value.y );
      m.addFloatArg( value.z );
    };

    void update_msg( const ofColor& value )
    { 
      m.addIntArg( value.r );
      m.addIntArg( value.g );
      m.addIntArg( value.b );
      m.addIntArg( value.a );
    };

    void update_msg( const ofFloatColor& value )
    { 
      m.addFloatArg( value.r );
      m.addFloatArg( value.g );
      m.addFloatArg( value.b );
      m.addFloatArg( value.a );
    };


    ofxOscSender* sender;
    ofxOscMessage m;
    ofParameter<T> _param;
};
