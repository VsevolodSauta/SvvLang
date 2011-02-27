RTranslatorError := Object clone
RTranslatorError with := method(msg, line,
	"#{line rawLineNumber}: Error: #{msg}" interpolate println
	System exit(-1)
)
