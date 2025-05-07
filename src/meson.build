readinglog_sources = [
  'main.c',
  'readinglog-application.c',
  'readinglog-window.c',
  'main-widget.c'
]

readinglog_deps = [
  dependency('gtk4'),
]

readinglog_sources += gnome.compile_resources('readinglog-resources',
  'readinglog.gresource.xml',
  c_name: 'readinglog'
)

executable('readinglog', readinglog_sources,
  dependencies: readinglog_deps,
       install: true,
)
