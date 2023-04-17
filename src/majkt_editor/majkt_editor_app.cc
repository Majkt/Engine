#include "src/lib/majkt_export.h"
#include "src/lib/entry_point.h"

#include "src/majkt_editor/editor_layer.h"

namespace majkt {

	class MajktEditor : public Application
	{
	public:
		MajktEditor()
			: Application("Majkt Editor")
		{
			PushLayer(new EditorLayer());
		}

		~MajktEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new MajktEditor();
	}

} // namespace majkt
