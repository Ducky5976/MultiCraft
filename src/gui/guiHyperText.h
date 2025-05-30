/*
Minetest
Copyright (C) 2019 EvicenceBKidscode / Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3.0 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once

#include "config.h" // for USE_FREETYPE
#include "StyleSpec.h"

using namespace irr;

class ISimpleTextureSource;
class ISoundManager;
class Client;

#if USE_FREETYPE
#include "irrlicht_changes/CGUITTFont.h"
#endif

class ParsedText
{
public:
	ParsedText(const wchar_t *text);
	~ParsedText();

	enum ElementType
	{
		ELEMENT_TEXT,
		ELEMENT_SEPARATOR,
		ELEMENT_IMAGE,
		ELEMENT_ITEM
	};

	enum BackgroundType
	{
		BACKGROUND_NONE,
		BACKGROUND_COLOR
	};

	enum FloatType
	{
		FLOAT_NONE,
		FLOAT_RIGHT,
		FLOAT_LEFT
	};

	enum HalignType
	{
		HALIGN_CENTER,
		HALIGN_LEFT,
		HALIGN_RIGHT,
		HALIGN_JUSTIFY
	};

	enum ValignType
	{
		VALIGN_MIDDLE,
		VALIGN_TOP,
		VALIGN_BOTTOM
	};

	typedef std::unordered_map<std::string, std::string> StyleList;
	typedef std::unordered_map<std::string, std::string> AttrsList;

	struct Tag
	{
		std::string name;
		AttrsList attrs;
		StyleList style;
	};

	struct Element
	{
		std::list<Tag *> tags;
		ElementType type;
		core::stringw text = "";

		core::dimension2d<u32> dim;
		core::position2d<s32> pos;
		s32 drawwidth;

		FloatType floating = FLOAT_NONE;

		ValignType valign;

		gui::IGUIFont *font;

		irr::video::SColor color;
		irr::video::SColor hovercolor;
		bool underline;

		s32 baseline = 0;

		// img & item specific attributes
		std::string name;
		v3s16 angle{0, 0, 0};
		v3s16 rotation{0, 0, 0};

		s32 margin = 10;

		void setStyle(StyleList &style);
	};

	struct Paragraph
	{
		std::vector<Element> elements;
		HalignType halign;
		s32 margin = 10;

		void setStyle(StyleList &style);
	};

	std::vector<Paragraph> m_paragraphs;

	// Element style
	s32 margin = 3;
	ValignType valign = VALIGN_TOP;
	BackgroundType background_type = BACKGROUND_NONE;
	irr::video::SColor background_color;

	Tag m_root_tag;

protected:
	typedef enum { ER_NONE, ER_TAG, ER_NEWLINE } EndReason;

	// Parser functions
	void enterElement(ElementType type);
	void endElement();
	void enterParagraph();
	void endParagraph(EndReason reason);
	void pushChar(wchar_t c);
	ParsedText::Tag *newTag(const std::string &name, const AttrsList &attrs);
	ParsedText::Tag *openTag(const std::string &name, const AttrsList &attrs);
	bool closeTag(const std::string &name);
	void parseGenericStyleAttr(const std::string &name, const std::string &value,
			StyleList &style);
	void parseStyles(const AttrsList &attrs, StyleList &style);
	void globalTag(const ParsedText::AttrsList &attrs);
	u32 parseTag(const wchar_t *text, u32 cursor);
	void parse(const wchar_t *text);

	std::unordered_map<std::string, StyleList> m_elementtags;
	std::unordered_map<std::string, StyleList> m_paragraphtags;

	std::vector<Tag *> m_not_root_tags;
	std::list<Tag *> m_active_tags;

	// Current values
	StyleList m_style;
	Element *m_element;
	Paragraph *m_paragraph;
	bool m_empty_paragraph;
	EndReason m_end_paragraph_reason;
};

class TextDrawer
{
public:
	TextDrawer(const wchar_t *text, Client *client, gui::IGUIEnvironment *environment,
			ISimpleTextureSource *tsrc);

	void place(const core::rect<s32> &dest_rect);
	inline s32 getHeight() { return m_height; };
	void draw(const core::rect<s32> &clip_rect,
			const core::position2d<s32> &dest_offset);
	ParsedText::Element *getElementAt(core::position2d<s32> pos);
	ParsedText::Tag *m_hovertag;

protected:
	struct RectWithMargin
	{
		core::rect<s32> rect;
		s32 margin;
	};

	ParsedText m_text;
	Client *m_client;
	gui::IGUIEnvironment *m_environment;
	s32 m_height;
	s32 m_voffset;
	std::vector<RectWithMargin> m_floating;
};

class GUIHyperText : public gui::IGUIElement
{
public:
	//! constructor
	GUIHyperText(const wchar_t *text, gui::IGUIEnvironment *environment,
			gui::IGUIElement *parent, s32 id,
			const core::rect<s32> &rectangle, Client *client,
			ISimpleTextureSource *tsrc, const StyleSpec &style,
			ISoundManager *sound_manager);

	//! destructor
	virtual ~GUIHyperText();

	//! draws the element and its children
	virtual void draw();

	core::dimension2du getTextDimension();

	bool OnEvent(const SEvent &event);

protected:
	// GUI members
	Client *m_client;
	GUIScrollBar *m_vscrollbar;
	TextDrawer m_drawer;

	// Positioning
	u32 m_scrollbar_width;
	core::rect<s32> m_display_text_rect;
	core::position2d<s32> m_text_scrollpos;

	ParsedText::Element *getElementAt(s32 X, s32 Y);
	void checkHover(s32 X, s32 Y);

	bool m_swipe_started;
	int m_swipe_start_y;
	float m_swipe_pos;
	ParsedText::Element *m_pressed_element = nullptr;
};
