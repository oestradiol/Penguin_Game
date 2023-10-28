#include "Rect.h"

class Collision {
	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB);
};