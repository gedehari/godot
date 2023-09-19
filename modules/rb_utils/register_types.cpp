#include "register_types.h"

#include "core/object/class_db.h"
#include "core/os/memory.h"
#include "rb_audio_preview.h"
#include "rb_audio_preview_rect.h"

static RBAudioPreviewGenerator *rb_audio_preview_generator = nullptr;

void initialize_rb_utils_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	rb_audio_preview_generator = memnew(RBAudioPreviewGenerator);
	ClassDB::register_class<RBAudioPreviewGenerator>();
	ClassDB::register_class<RBAudioPreview>();
	ClassDB::register_class<RBAudioPreviewRect>();
	Engine::get_singleton()->add_singleton(Engine::Singleton("RBAudioPreviewGenerator", RBAudioPreviewGenerator::get_singleton()));
}

void uninitialize_rb_utils_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	memdelete(rb_audio_preview_generator);
	rb_audio_preview_generator = nullptr;
}