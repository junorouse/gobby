/* gobby - A GTKmm driven libobby client
 * Copyright (C) 2005 0x539 dev group
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _GOBBY_FOLDER_HPP_
#define _GOBBY_FOLDER_HPP_

#include <sigc++/signal.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/notebook.h>
#include <obby/user.hpp>
#include <obby/document.hpp>
#include <obby/local_buffer.hpp>

#include "document.hpp"

#ifdef WITH_GTKSOURCEVIEW
# include "sourceview/sourcelanguage.hpp"
# include "sourceview/sourcelanguagesmanager.hpp"
# include "mimemap.hpp"
#endif

namespace Gobby
{

/** Thing containing multiple documents.
 */
	
class Folder : public Gtk::Notebook
{
public:
	class TabLabel : public Gtk::HBox
	{
	public:
		typedef Glib::SignalProxy0<void> close_signal_type;

		TabLabel(const Glib::ustring& label);
		~TabLabel();

		close_signal_type close_event();
	protected:
		Gtk::Image m_image;
		Gtk::Label m_label;
		Gtk::Button m_button;
		Gtk::HBox m_box;
	};

	typedef sigc::signal<void, Document&> signal_document_close_type;
	typedef sigc::signal<void, Document&> signal_document_cursor_moved_type;
	typedef sigc::signal<void, Document&>
		signal_document_content_changed_type;
#ifdef WITH_GTKSOURCEVIEW
	typedef sigc::signal<void, Document&>
		signal_document_language_changed_type;
#endif
	typedef sigc::signal<void, Document&> signal_tab_switched_type;

	Folder();
	~Folder();

#ifdef WITH_GTKSOURCEVIEW
	// Access to the mime map
	const MimeMap& get_mime_map() const;

	Glib::RefPtr<Gtk::SourceLanguagesManager> get_lang_manager() const;
#endif

	// Calls from the window
	void obby_start(obby::local_buffer& buf);
	void obby_end();
	void obby_user_join(obby::user& user);
	void obby_user_part(obby::user& user);
	void obby_document_insert(obby::local_document_info& document);
	void obby_document_remove(obby::local_document_info& document);

	signal_document_close_type document_close_event() const;
	signal_document_cursor_moved_type document_cursor_moved_event() const;
	signal_document_content_changed_type
		document_content_changed_event() const;
#ifdef WITH_GTKSOURCEVIEW
	signal_document_language_changed_type
		document_language_changed_event() const;
#endif
	signal_tab_switched_type tab_switched_event() const;

protected:
	// Overrides
	virtual void on_switch_page(GtkNotebookPage* page, guint page_num);

	// Signal handlers
	void on_document_close(Document& document);

	void on_document_cursor_moved(Document& document);
	void on_document_content_changed(Document& document);
#ifdef WITH_GTKSOURCEVIEW
	void on_document_language_changed(Document& document);
#endif

	signal_document_close_type m_signal_document_close;
	signal_document_cursor_moved_type m_signal_document_cursor_moved;
	signal_document_content_changed_type m_signal_document_content_changed;
#ifdef WITH_GTKSOURCEVIEW
	signal_document_language_changed_type
		m_signal_document_language_changed;
#endif
	signal_tab_switched_type m_signal_tab_switched;

	/** Signals whether the obby session is running.
	 */
	bool m_running;

#ifdef WITH_GTKSOURCEVIEW
	Glib::RefPtr<Gtk::SourceLanguagesManager> m_lang_manager;
	MimeMap m_mime_map;
#endif
};

}

#endif // _GOBBY_FOLDER_HPP_
