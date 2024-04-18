#include "Object.h"

// Object methods///////////////////////////////////////////////////////////////////////////////////
Object::Object(std::string file, float x, float y) {
	
	texture.loadFromFile(file);
	sprite.setTexture(texture);
	rect.width = sprite.getTextureRect().width;
	rect.height = sprite.getTextureRect().height;
	rect.left = x;
	rect.top = y;
	sprite.setPosition(rect.left, rect.top);
}
void Object::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}
sf::Sprite Object::getSprite() {
	return sprite;
}


TmxObject::TmxObject(sf::FloatRect rect, std::string file, std::string type_name) {
	Object::Object(file, rect.left, rect.top);
	bdef.position.Set((rect.left + rect.width / 2) / SCALE, (rect.top + rect.height / 2) / SCALE);
	body = world.CreateBody(&bdef);
	box.SetAsBox((rect.width / 2) / SCALE, (rect.height / 2) / SCALE);
	body->CreateFixture(&box, 0.0f);
	name = type_name;
}
sf::Sprite TmxObject::getSprite() {
	return sprite;
}
void TmxObject::update(sf::RenderWindow& window) {
	
}
void TmxObject::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}
void TmxObject::setPhysics() {

	bdef.position.Set((rect.left + rect.width / 2) / SCALE, (rect.top + rect.height / 2) / SCALE);
	body = world.CreateBody(&bdef);
	box.SetAsBox((rect.width / 2) / SCALE, (rect.height / 2) / SCALE);
	body->CreateFixture(&box, 0.0f);
}


DynamicObject::DynamicObject(TmxObject obj) {
	sprite = obj.getSprite();
	rect = obj.rect;

	//bdef = obj.bdef;
	bdef.type = b2_dynamicBody;
	bdef.position.Set(rect.left / SCALE, rect.top / SCALE);

	body = world.CreateBody(&bdef);
	box.SetAsBox((rect.width / 2) / SCALE, (rect.height / 2) / SCALE);
	speed = 400.f;
	fdef.shape = &box;
	fdef.density = 1.0f;
	
	body->CreateFixture(&fdef);
	angle = 0.f;

	name = obj.name;
	type = obj.type;
	properties = obj.properties;
}
sf::Sprite DynamicObject::getSprite() {
	return sprite;
}
void DynamicObject::input(sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		body->ApplyForceToCenter(b2Vec2(-speed, 0.f), true);
		b2Vec2 p = b2Vec2(body->GetPosition().x, body->GetPosition().y);
		float x = p.x;
		//body->ApplyLinearImpulseToCenter(b2Vec2(-speed, 0.f), false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		//body->ApplyForceToCenter(b2Vec2(speed, 0.f), false);
		//body->SetLinearVelocity(b2Vec2(speed, 0.f));
	}
}
void DynamicObject::update(sf::RenderWindow& window) {
 	//b2Vec2 p = body->GetPosition();
	//float angle = body->GetAngle();
	//sprite.setPosition(p.x*SCALE, p.y*SCALE);
	//sprite.setRotation(angle*DEG);
}
void DynamicObject::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}




// PushButton methods///////////////////////////////////////////////////////////////////////////////////
PushButton::PushButton(std::string file,sf::FloatRect r, sf::Color b_color, sf::Color c_color) {
	rect = r;

	texture.loadFromFile(file);
	rect.width = texture.getSize().x;
	rect.height = texture.getSize().y;

	sprite.setTexture(texture, &rect);
	sprite.setPosition(rect.left, rect.top);
	base_color = b_color;
	clicked_color = c_color;
	is_clicked = false;
	
}
void PushButton::input(sf::RenderWindow& window) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (is_pos(window))
			State.CurrState = true;
	}

	bool IsPressedAndReleased = State.pick();
	if (is_pos(window) && IsPressedAndReleased)
		std::invoke(OnClick);
}
void PushButton::update(sf::RenderWindow& window) {
	if (is_pos(window) || is_clicked) 
		sprite.setColor(clicked_color);
	else if (!is_clicked && !is_pos(window))
		sprite.setColor(base_color);
}
void PushButton::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}
bool  PushButton::is_pos(sf::RenderWindow& window) {
	sf::IntRect r(rect.left, rect.top, rect.width, rect.height);
	if (r.contains(sf::Mouse::getPosition(window))) {
		return true;
	}
	return false;
}
sf::Sprite PushButton::getSprite() {
	return sprite;
}
bool PushButton::ButtonClick::pick() {
	// Button is pushed in current frame.
	if (CurrState) {
		PrevState = true;
		CurrState = false;
		return false;
	}
	// Here CurrState is false (button released)
	if (PrevState) {// Prev frame button was pushed
		PrevState = false;
		CurrState = false;
		return true;
	}
	// Prev frame nothig happens
	PrevState = false;
	CurrState = false;
	return false;
}