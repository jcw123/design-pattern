### BasicTokenSource
> 用来解析pointcut中的表达式

#### 核心代码

```java
public static ITokenSource makeTokenSource(String input, ISourceContext context) {
		char[] chars = input.toCharArray();
		
		int i = 0;
		List<BasicToken> tokens = new ArrayList<BasicToken>();
		
		while (i < chars.length) {
			char ch = chars[i++];			
			switch(ch) {
				case ' ':
				case '\t':
				case '\n':
				case '\r':
					continue;
				case '*':
				case '(':
				case ')':
				case '+':
				case '[':
				case ']':
				case ',':
				case '!':
				case ':':
				case '@':
				case '<':
				case '>':
				case '=':
				case 	'?':
				    tokens.add(BasicToken.makeOperator(makeString(ch), i-1, i-1));
				    continue;
				case '.':
					if ((i+2)<=chars.length) {
						// could be '...'
						char nextChar1 = chars[i];
						char nextChar2 = chars[i+1];
						if (ch==nextChar1 && ch==nextChar2) {
							// '...'
							tokens.add(BasicToken.makeIdentifier("...",i-1,i+1));
							i=i+2;
						} else {
							tokens.add(BasicToken.makeOperator(makeString(ch), i-1, i-1));
						}
					} else {
						tokens.add(BasicToken.makeOperator(makeString(ch), i-1, i-1));
					}
					continue;
				case '&':
					if ((i+1) <= chars.length && chars[i] != '&') {
						tokens.add(BasicToken.makeOperator(makeString(ch),i-1,i-1));
						continue;
					}
					// fall-through
				case '|':
				    if (i == chars.length) {
				    	throw new BCException("bad " + ch);
				    }
				    char nextChar = chars[i++];
				    if (nextChar == ch) {
				    	tokens.add(BasicToken.makeOperator(makeString(ch, 2), i-2, i-1));
				    } else {
				    	throw new RuntimeException("bad " + ch);
				    }
				    continue;
				    
				case '\"':
				    int start0 = i-1;
				    while (i < chars.length && !(chars[i]=='\"')) i++;
				    i += 1;
				    tokens.add(BasicToken.makeLiteral(new String(chars, start0+1, i-start0-2), "string", start0, i-1));
				    continue;
				default:
				    int start = i-1;
				    while (i < chars.length && Character.isJavaIdentifierPart(chars[i])) { i++; }
				    tokens.add(BasicToken.makeIdentifier(new String(chars, start, i-start), start, i-1));
				
			}
		}

		//System.out.println(tokens);
		
		return new BasicTokenSource((IToken[])tokens.toArray(new IToken[tokens.size()]), context);
	}
```


