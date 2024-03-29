// Generated from YouVerify.g4 by ANTLR 4.9
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class YouVerifyLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, BOOLEAN=24, 
		OPERATOR=25, TERNARY_OPERATOR=26, IDENTIFIER=27, INTEGER=28, NEWLINE=29, 
		ARROW=30, COMMA=31, OPAREN=32, CPAREN=33, COLON=34, PERIOD=35, TAB=36, 
		WHITESPACE=37;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
			"T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "BOOLEAN", "OPERATOR", 
			"TERNARY_OPERATOR", "IDENTIFIER", "INTEGER", "NEWLINE", "ARROW", "COMMA", 
			"OPAREN", "CPAREN", "COLON", "PERIOD", "TAB", "WHITESPACE"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'define'", "'record'", "'LABEL'", "'return'", "'assume'", "'assert'", 
			"'='", "'call'", "'new'", "'$sym'", "'{'", "'}'", "'if'", "'goto'", "'ARRAY[]'", 
			"'ARRAY['", "']'", "'BV'", "'*'", "'['", "'BOOL'", "'INT'", "'ARRAY'", 
			null, null, "'?'", null, null, null, "'->'", "','", "'('", "')'", "':'", 
			"'.'", "'\t'", "' '"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			"BOOLEAN", "OPERATOR", "TERNARY_OPERATOR", "IDENTIFIER", "INTEGER", "NEWLINE", 
			"ARROW", "COMMA", "OPAREN", "CPAREN", "COLON", "PERIOD", "TAB", "WHITESPACE"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public YouVerifyLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "YouVerify.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\'\u0103\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5"+
		"\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\b\3\b\3"+
		"\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\f\3\f\3"+
		"\r\3\r\3\16\3\16\3\16\3\17\3\17\3\17\3\17\3\17\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3\22\3\22\3\23\3\23"+
		"\3\23\3\24\3\24\3\25\3\25\3\26\3\26\3\26\3\26\3\26\3\27\3\27\3\27\3\27"+
		"\3\30\3\30\3\30\3\30\3\30\3\30\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31"+
		"\3\31\5\31\u00c3\n\31\3\32\3\32\3\32\3\32\3\32\3\32\3\32\3\32\3\32\3\32"+
		"\3\32\3\32\3\32\3\32\5\32\u00d3\n\32\3\33\3\33\3\34\3\34\7\34\u00d9\n"+
		"\34\f\34\16\34\u00dc\13\34\3\35\3\35\3\35\7\35\u00e1\n\35\f\35\16\35\u00e4"+
		"\13\35\5\35\u00e6\n\35\3\36\5\36\u00e9\n\36\3\36\3\36\6\36\u00ed\n\36"+
		"\r\36\16\36\u00ee\3\37\3\37\3\37\3 \3 \3!\3!\3\"\3\"\3#\3#\3$\3$\3%\3"+
		"%\3&\3&\3&\3&\2\2\'\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r"+
		"\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33"+
		"\65\34\67\359\36;\37= ?!A\"C#E$G%I&K\'\3\2\t\5\2((``~~\6\2\'\',-//\61"+
		"\61\5\2##@@BB\4\2C\\c|\6\2\62;C\\aac|\3\2\63;\3\2\62;\2\u0111\2\3\3\2"+
		"\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17"+
		"\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2"+
		"\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3"+
		"\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3"+
		"\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2"+
		"=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3"+
		"\2\2\2\2K\3\2\2\2\3M\3\2\2\2\5T\3\2\2\2\7[\3\2\2\2\ta\3\2\2\2\13h\3\2"+
		"\2\2\ro\3\2\2\2\17v\3\2\2\2\21x\3\2\2\2\23}\3\2\2\2\25\u0081\3\2\2\2\27"+
		"\u0086\3\2\2\2\31\u0088\3\2\2\2\33\u008a\3\2\2\2\35\u008d\3\2\2\2\37\u0092"+
		"\3\2\2\2!\u009a\3\2\2\2#\u00a1\3\2\2\2%\u00a3\3\2\2\2\'\u00a6\3\2\2\2"+
		")\u00a8\3\2\2\2+\u00aa\3\2\2\2-\u00af\3\2\2\2/\u00b3\3\2\2\2\61\u00c2"+
		"\3\2\2\2\63\u00d2\3\2\2\2\65\u00d4\3\2\2\2\67\u00d6\3\2\2\29\u00e5\3\2"+
		"\2\2;\u00ec\3\2\2\2=\u00f0\3\2\2\2?\u00f3\3\2\2\2A\u00f5\3\2\2\2C\u00f7"+
		"\3\2\2\2E\u00f9\3\2\2\2G\u00fb\3\2\2\2I\u00fd\3\2\2\2K\u00ff\3\2\2\2M"+
		"N\7f\2\2NO\7g\2\2OP\7h\2\2PQ\7k\2\2QR\7p\2\2RS\7g\2\2S\4\3\2\2\2TU\7t"+
		"\2\2UV\7g\2\2VW\7e\2\2WX\7q\2\2XY\7t\2\2YZ\7f\2\2Z\6\3\2\2\2[\\\7N\2\2"+
		"\\]\7C\2\2]^\7D\2\2^_\7G\2\2_`\7N\2\2`\b\3\2\2\2ab\7t\2\2bc\7g\2\2cd\7"+
		"v\2\2de\7w\2\2ef\7t\2\2fg\7p\2\2g\n\3\2\2\2hi\7c\2\2ij\7u\2\2jk\7u\2\2"+
		"kl\7w\2\2lm\7o\2\2mn\7g\2\2n\f\3\2\2\2op\7c\2\2pq\7u\2\2qr\7u\2\2rs\7"+
		"g\2\2st\7t\2\2tu\7v\2\2u\16\3\2\2\2vw\7?\2\2w\20\3\2\2\2xy\7e\2\2yz\7"+
		"c\2\2z{\7n\2\2{|\7n\2\2|\22\3\2\2\2}~\7p\2\2~\177\7g\2\2\177\u0080\7y"+
		"\2\2\u0080\24\3\2\2\2\u0081\u0082\7&\2\2\u0082\u0083\7u\2\2\u0083\u0084"+
		"\7{\2\2\u0084\u0085\7o\2\2\u0085\26\3\2\2\2\u0086\u0087\7}\2\2\u0087\30"+
		"\3\2\2\2\u0088\u0089\7\177\2\2\u0089\32\3\2\2\2\u008a\u008b\7k\2\2\u008b"+
		"\u008c\7h\2\2\u008c\34\3\2\2\2\u008d\u008e\7i\2\2\u008e\u008f\7q\2\2\u008f"+
		"\u0090\7v\2\2\u0090\u0091\7q\2\2\u0091\36\3\2\2\2\u0092\u0093\7C\2\2\u0093"+
		"\u0094\7T\2\2\u0094\u0095\7T\2\2\u0095\u0096\7C\2\2\u0096\u0097\7[\2\2"+
		"\u0097\u0098\7]\2\2\u0098\u0099\7_\2\2\u0099 \3\2\2\2\u009a\u009b\7C\2"+
		"\2\u009b\u009c\7T\2\2\u009c\u009d\7T\2\2\u009d\u009e\7C\2\2\u009e\u009f"+
		"\7[\2\2\u009f\u00a0\7]\2\2\u00a0\"\3\2\2\2\u00a1\u00a2\7_\2\2\u00a2$\3"+
		"\2\2\2\u00a3\u00a4\7D\2\2\u00a4\u00a5\7X\2\2\u00a5&\3\2\2\2\u00a6\u00a7"+
		"\7,\2\2\u00a7(\3\2\2\2\u00a8\u00a9\7]\2\2\u00a9*\3\2\2\2\u00aa\u00ab\7"+
		"D\2\2\u00ab\u00ac\7Q\2\2\u00ac\u00ad\7Q\2\2\u00ad\u00ae\7N\2\2\u00ae,"+
		"\3\2\2\2\u00af\u00b0\7K\2\2\u00b0\u00b1\7P\2\2\u00b1\u00b2\7V\2\2\u00b2"+
		".\3\2\2\2\u00b3\u00b4\7C\2\2\u00b4\u00b5\7T\2\2\u00b5\u00b6\7T\2\2\u00b6"+
		"\u00b7\7C\2\2\u00b7\u00b8\7[\2\2\u00b8\60\3\2\2\2\u00b9\u00ba\7v\2\2\u00ba"+
		"\u00bb\7t\2\2\u00bb\u00bc\7w\2\2\u00bc\u00c3\7g\2\2\u00bd\u00be\7h\2\2"+
		"\u00be\u00bf\7c\2\2\u00bf\u00c0\7n\2\2\u00c0\u00c1\7u\2\2\u00c1\u00c3"+
		"\7g\2\2\u00c2\u00b9\3\2\2\2\u00c2\u00bd\3\2\2\2\u00c3\62\3\2\2\2\u00c4"+
		"\u00d3\t\2\2\2\u00c5\u00c6\7?\2\2\u00c6\u00d3\7@\2\2\u00c7\u00c8\7?\2"+
		"\2\u00c8\u00d3\7?\2\2\u00c9\u00ca\7#\2\2\u00ca\u00d3\7?\2\2\u00cb\u00d3"+
		"\t\3\2\2\u00cc\u00cd\7>\2\2\u00cd\u00d3\7?\2\2\u00ce\u00d3\7>\2\2\u00cf"+
		"\u00d0\7@\2\2\u00d0\u00d3\7?\2\2\u00d1\u00d3\t\4\2\2\u00d2\u00c4\3\2\2"+
		"\2\u00d2\u00c5\3\2\2\2\u00d2\u00c7\3\2\2\2\u00d2\u00c9\3\2\2\2\u00d2\u00cb"+
		"\3\2\2\2\u00d2\u00cc\3\2\2\2\u00d2\u00ce\3\2\2\2\u00d2\u00cf\3\2\2\2\u00d2"+
		"\u00d1\3\2\2\2\u00d3\64\3\2\2\2\u00d4\u00d5\7A\2\2\u00d5\66\3\2\2\2\u00d6"+
		"\u00da\t\5\2\2\u00d7\u00d9\t\6\2\2\u00d8\u00d7\3\2\2\2\u00d9\u00dc\3\2"+
		"\2\2\u00da\u00d8\3\2\2\2\u00da\u00db\3\2\2\2\u00db8\3\2\2\2\u00dc\u00da"+
		"\3\2\2\2\u00dd\u00e6\7\62\2\2\u00de\u00e2\t\7\2\2\u00df\u00e1\t\b\2\2"+
		"\u00e0\u00df\3\2\2\2\u00e1\u00e4\3\2\2\2\u00e2\u00e0\3\2\2\2\u00e2\u00e3"+
		"\3\2\2\2\u00e3\u00e6\3\2\2\2\u00e4\u00e2\3\2\2\2\u00e5\u00dd\3\2\2\2\u00e5"+
		"\u00de\3\2\2\2\u00e6:\3\2\2\2\u00e7\u00e9\7\17\2\2\u00e8\u00e7\3\2\2\2"+
		"\u00e8\u00e9\3\2\2\2\u00e9\u00ea\3\2\2\2\u00ea\u00ed\7\f\2\2\u00eb\u00ed"+
		"\7\17\2\2\u00ec\u00e8\3\2\2\2\u00ec\u00eb\3\2\2\2\u00ed\u00ee\3\2\2\2"+
		"\u00ee\u00ec\3\2\2\2\u00ee\u00ef\3\2\2\2\u00ef<\3\2\2\2\u00f0\u00f1\7"+
		"/\2\2\u00f1\u00f2\7@\2\2\u00f2>\3\2\2\2\u00f3\u00f4\7.\2\2\u00f4@\3\2"+
		"\2\2\u00f5\u00f6\7*\2\2\u00f6B\3\2\2\2\u00f7\u00f8\7+\2\2\u00f8D\3\2\2"+
		"\2\u00f9\u00fa\7<\2\2\u00faF\3\2\2\2\u00fb\u00fc\7\60\2\2\u00fcH\3\2\2"+
		"\2\u00fd\u00fe\7\13\2\2\u00feJ\3\2\2\2\u00ff\u0100\7\"\2\2\u0100\u0101"+
		"\3\2\2\2\u0101\u0102\b&\2\2\u0102L\3\2\2\2\f\2\u00c2\u00d2\u00d8\u00da"+
		"\u00e2\u00e5\u00e8\u00ec\u00ee\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}