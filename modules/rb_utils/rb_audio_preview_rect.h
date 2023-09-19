#ifndef RB_AUDIO_PREVIEW_RECT_H
#define RB_AUDIO_PREVIEW_RECT_H

#include "core/object/object.h"
#include "scene/gui/color_rect.h"
#include "servers/audio/audio_stream.h"

class RBAudioPreviewRect : public ColorRect {
	GDCLASS(RBAudioPreviewRect, ColorRect)

	Ref<AudioStream> stream;
	Color waveform_color = Color(0, 0, 0);
	float preview_offset;
	float preview_len;

protected:
	static void _bind_methods();

	void _notification(int p_what);

	void _draw_preview();

public:
	RBAudioPreviewRect();

	void set_stream(Ref<AudioStream> p_stream);
	Ref<AudioStream> get_stream() const;

	void set_waveform_color(Color p_color);
	Color get_waveform_color() const;

	void set_preview_offset(float p_offset);
	float get_preview_offset() const;

	void set_preview_len(float p_len);
	float get_preview_len() const;
};

#endif