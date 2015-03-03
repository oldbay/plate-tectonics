#ifndef BOUNDS_HPP
#define BOUNDS_HPP

#include "simplerandom.hpp"
#include "heightmap.hpp"
#include "rectangle.hpp"
#include "segment_data.hpp"
#include "utils.hpp"

class Bounds {
public:
	Bounds(const WorldDimension& worldDimension, const FloatPoint& position, const Dimension& dimension)
		: _worldDimension(worldDimension), 
		  _position(position), 
		  _dimension(dimension) {

	};
	uint32_t index(uint32_t x, uint32_t y) const{
		return y * _dimension.getWidth() + x;
	} 	
	uint32_t area() const{
		return _dimension.getArea();
	}
	uint32_t width() const {
		return _dimension.getWidth();
	}
	uint32_t height() const {
		return _dimension.getHeight();
	}
	float left() const {
		return _position.getX();
	}
	float top() const {
		return _position.getY();
	}	
	float right() const {
		return left() + width() - 1;
	}
	float bottom() const {
		return top() + height() - 1;
	}
	bool contains(uint32_t x, uint32_t y) const{
		uint32_t cleanX = xMod(x);
    	uint32_t cleanY = yMod(y);
		return cleanX >= _position.getX() && cleanX<(_position.getX() + _dimension.getWidth()) 
        	&& cleanY >= _position.getY() && cleanY<(_position.getY() + _dimension.getHeight());
	}
	uint32_t xMod(uint32_t x) const
	{
	    return (x + _worldDimension.getWidth()) % _worldDimension.getWidth();
	}

	uint32_t yMod(uint32_t y) const
	{
	    return (y + _worldDimension.getHeight()) % _worldDimension.getHeight();
	}
	void grow(float dx, float dy){
		_position.grow(dx, dy, _worldDimension);
		p_assert(_worldDimension.contains(_position), "");
	}
	void growWidth(int d){
		_dimension.growWidth(d);
	}
	void growHeight(int d){
		_dimension.growHeight(d);
	}	
	Platec::Rectangle asRect() const
	{
	    p_assert(_position.getX() >= 0.0f && _position.getY() >= 0.0f, "Left and top must be positive");  
	    const uint32_t ilft = (uint32_t)_position.getX();
	    const uint32_t itop = (uint32_t)_position.getY();
	    const uint32_t irgt = ilft + _dimension.getWidth();
	    const uint32_t ibtm = itop + _dimension.getHeight();

	    return Platec::Rectangle(_worldDimension, ilft, irgt, itop, ibtm);     
	}
private:
	const WorldDimension _worldDimension;
	FloatPoint _position;
	Dimension _dimension;	
};

#endif
