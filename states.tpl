/*$i=0$*/
switch(/*$ state $*/){
	/*$ for s in $*/
	case /*$s.stateName$*/:
		/*$s.doBlock$*/

		/*$ for(t in s.trigger_list)$*/
		/*$if(i!=0){$*/else/*$}$*/if(/*$e(t.triggerName)$*/){
			/*$n = t.nextState$*/
			/*$s.exitBlock$*/
			/*$n.entryBlock$*/
			/*$$*/
			/*$state$*/ = /*$n.stateName$*/;
			/*$i = i + 1$*/
		}
		/*$ end $*/
	/*$ end $*/
	default:
		break;
}