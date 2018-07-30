function toggle(_this)
　　	{
　　		var img = _this.getElementsByTagName("img")[0];
　　		if (_this.state && _this.state == 'out') {
　　			img.src = "../picture/team-zhangjiaxi2.jpg";
　　			_this.state = 'over'
　　		}
			else {
　　			img.src = "../picture/team-zhangjiaxi-r1.jpg";
　　			_this.state = 'out'
　　		}
　　	}
function toggle1(_this)
{
　　var img = _this.getElementsByTagName("img")[0];
　　if (_this.state && _this.state == 'out') {
　　	img.src = "../picture/team-xurunbang1.jpg";
　　	_this.state = 'over'
　　}
	else {
　　	img.src = "../picture/team-xurunbang3.jpg";
　　	_this.state = 'out'
　　}
}
function toggle2(_this)
{
　　var img = _this.getElementsByTagName("img")[0];
　　if (_this.state && _this.state == 'out') {
　　	img.src = "../picture/team_yangqixuan2.jpg";
　　	_this.state = 'over'
　　}
	else {
　　	img.src = "../picture/team_yangqixuan1.jpg";
　　	_this.state = 'out'
　　}
}
function toggle3(_this)
{
　　var img = _this.getElementsByTagName("img")[0];
　　if (_this.state && _this.state == 'out') {
　　	img.src = "../picture/team_mayizhan1.jpg";
　　	_this.state = 'over'
　　}
	else {
　　	img.src = "../picture/team_mayizhan2.jpg";
　　	_this.state = 'out'
　　}
}