#ifndef _AABBOXH_
#define _AABBOXH_

#include <cfloat>
#include <algorithm>

#include "../math/vector3d.h"
#include "../ray/ray.h"

namespace Orchid
{
	// Axis-aligned bounding box
	struct AABBox {
		Vector3d bl;     // Bottom left (min)
		Vector3d tr;     // Top right   (max)

		AABBox(Vector3d bl_ = Vector3d(), Vector3d tr_ = Vector3d()) {
			bl = bl_, tr = tr_;
		}

		// Expand to fit box
		void expand(const AABBox &box) {
			if (box.bl.x() < bl.x()) bl[0] = box.bl.x();
			if (box.bl.y() < bl.y()) bl[1] = box.bl.y();
			if (box.bl.z() < bl.z()) bl[2] = box.bl.z();

			if (box.tr.x() > tr.x()) tr[0] = box.tr.x();
			if (box.tr.y() > tr.y()) tr[1] = box.tr.y();
			if (box.tr.z() > tr.z()) tr[2] = box.tr.z();
		}

		// Expand to fit point
		void expand(const Vector3d &vec) {
			if (vec.x() < bl.x()) bl[0] = vec.x();
			if (vec.y() < bl.y()) bl[1] = vec.y();
			if (vec.z() < bl.z()) bl[2] = vec.z();
		}

		// Returns longest axis: 0, 1, 2 for x, y, z respectively
		int get_longest_axis() {
			Vector3d diff = tr - bl;
			if (diff.x() > diff.y() && diff.x() > diff.z()) return 0;
			if (diff.y() > diff.x() && diff.y() > diff.z()) return 1;
			return 2;
		}

		// Check if ray intersects with box. Returns true/false and stores distance in t
		bool intersection(const Ray &r, double &t) {
			double tx1 = (bl.x() - r.origin().x())*r.invdir().x();
			double tx2 = (tr.x() - r.origin().x())*r.invdir().x();

			double tmin = std::min(tx1, tx2);
			double tmax = std::max(tx1, tx2);

			double ty1 = (bl.y() - r.origin().y())*r.invdir().y();
			double ty2 = (tr.y() - r.origin().y())*r.invdir().y();

			tmin = std::max(tmin, std::min(ty1, ty2));
			tmax = std::min(tmax, std::max(ty1, ty2));

			double tz1 = (bl.z() - r.origin().z())*r.invdir().z();
			double tz2 = (tr.z() - r.origin().z())*r.invdir().z();

			tmin = std::max(tmin, std::min(tz1, tz2));
			tmax = std::min(tmax, std::max(tz1, tz2));
			t = tmin;

			return tmax >= tmin;
		}
	};
}

#endif // !_AABBOXH_
