namespace Raytracer {

class Material {

};

class Primitive {
public:
	float getLight(){ return m_Light; };
private:
    Material m_Material;
	char* m_Name;
	bool m_Light;
};

class Sphere : public Primitive {
	
};

}