#include "rb_audio_preview_rect.h"

#include "core/math/color.h"
#include "core/math/vector2.h"
#include "core/object/class_db.h"
#include "editor/audio_stream_preview.h"
#include "modules/rb_utils/rb_audio_preview.h"

void RBAudioPreviewRect::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_stream", "stream"), &RBAudioPreviewRect::set_stream);
	ClassDB::bind_method(D_METHOD("get_stream"), &RBAudioPreviewRect::get_stream);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stream", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_stream", "get_stream");

	ClassDB::bind_method(D_METHOD("set_waveform_color", "color"), &RBAudioPreviewRect::set_waveform_color);
	ClassDB::bind_method(D_METHOD("get_waveform_color"), &RBAudioPreviewRect::get_waveform_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "waveform_color"), "set_waveform_color", "get_waveform_color");

	ClassDB::bind_method(D_METHOD("set_preview_offset", "offset"), &RBAudioPreviewRect::set_preview_offset);
	ClassDB::bind_method(D_METHOD("get_preview_offset"), &RBAudioPreviewRect::get_preview_offset);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "preview_offset"), "set_preview_offset", "get_preview_offset");

	ClassDB::bind_method(D_METHOD("set_preview_len", "len"), &RBAudioPreviewRect::set_preview_len);
	ClassDB::bind_method(D_METHOD("get_preview_len"), &RBAudioPreviewRect::get_preview_len);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "preview_len"), "set_preview_len", "get_preview_len");
}

void RBAudioPreviewRect::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_DRAW:
			_draw_preview();
			break;
	}
}

void RBAudioPreviewRect::_draw_preview() {
	if (stream.is_null()) {
		return;
	}

	Rect2 rect = get_rect();
	Size2 rect_size = rect.size;
	int width = rect_size.width;

	Ref<RBAudioPreview> preview = RBAudioPreviewGenerator::get_singleton()->generate_preview(stream);

	Vector<Vector2> points;
	points.resize(width * 2);
	Vector<Color> colors;
	colors.resize(width);

	for (int i = 0; i < width; i++) {
		float ofs = preview_offset + i * preview_len / rect_size.width;
		float ofs_n = preview_offset + (i + 1) * preview_len / rect_size.width;
		float max = preview->get_max(ofs, ofs_n) * 0.5 + 0.5;
		float min = preview->get_min(ofs, ofs_n) * 0.5 + 0.5;

		int idx = i;
		points.write[idx * 2 + 0] = Vector2(i + 1, rect.position.y + min * rect.size.y);
		points.write[idx * 2 + 1] = Vector2(i + 1, rect.position.y + max * rect.size.y);

		colors.write[idx] = waveform_color;
	}

	if (!points.is_empty()) {
		RS::get_singleton()->canvas_item_add_multiline(get_canvas_item(), points, colors);
	}
}

RBAudioPreviewRect::RBAudioPreviewRect() {
	preview_offset = 0;
	preview_len = 0;
}

void RBAudioPreviewRect::set_stream(Ref<AudioStream> p_stream) {
	stream = p_stream;
	queue_redraw();
}

Ref<AudioStream> RBAudioPreviewRect::get_stream() const {
	return stream;
}

void RBAudioPreviewRect::set_waveform_color(Color p_color) {
	waveform_color = p_color;
	queue_redraw();
}

Color RBAudioPreviewRect::get_waveform_color() const {
	return waveform_color;
}

void RBAudioPreviewRect::set_preview_offset(float p_offset) {
	preview_offset = p_offset;
	queue_redraw();
}

float RBAudioPreviewRect::get_preview_offset() const {
	return preview_offset;
}

void RBAudioPreviewRect::set_preview_len(float p_len) {
	preview_len = p_len;
	queue_redraw();
}

float RBAudioPreviewRect::get_preview_len() const {
	return preview_len;
}
