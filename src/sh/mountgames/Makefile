install:
	install -o root -g wheel -m 755 mountgames.sh /Users/Shared/mountgames
	install -o root -g wheel -m 644 com.andersbo.mountgames.plist /Library/LaunchDaemons/com.andersbo.mountgames.plist
	launchctl load -w /Library/LaunchDaemons/com.andersbo.mountgames.plist
