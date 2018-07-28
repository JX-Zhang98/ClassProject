namespace test1
{
    partial class ManagerTreeview
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("添加管理员信息");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("修改管理员信息");
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("管理员信息管理", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2});
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("添加学生信息");
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("修改学生信息");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("学生信息管理", new System.Windows.Forms.TreeNode[] {
            treeNode4,
            treeNode5});
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("添加教师信息");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("修改教师信息");
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("教师信息管理", new System.Windows.Forms.TreeNode[] {
            treeNode7,
            treeNode8});
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("用户管理", new System.Windows.Forms.TreeNode[] {
            treeNode3,
            treeNode6,
            treeNode9});
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("审核课程");
            System.Windows.Forms.TreeNode treeNode12 = new System.Windows.Forms.TreeNode("课程管理", new System.Windows.Forms.TreeNode[] {
            treeNode11});
            System.Windows.Forms.TreeNode treeNode13 = new System.Windows.Forms.TreeNode("修改密码");
            System.Windows.Forms.TreeNode treeNode14 = new System.Windows.Forms.TreeNode("关于");
            System.Windows.Forms.TreeNode treeNode15 = new System.Windows.Forms.TreeNode("退出系统");
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ManagerTreeview));
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.panel2 = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.treeView1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.treeView1.LineColor = System.Drawing.Color.LightGray;
            this.treeView1.Location = new System.Drawing.Point(13, 15);
            this.treeView1.Name = "treeView1";
            treeNode1.Name = "addMan";
            treeNode1.Text = "添加管理员信息";
            treeNode2.Name = "modifyMan";
            treeNode2.Text = "修改管理员信息";
            treeNode3.Name = "manMan";
            treeNode3.Text = "管理员信息管理";
            treeNode4.Name = "addStu";
            treeNode4.Text = "添加学生信息";
            treeNode5.Name = "modifyStu";
            treeNode5.Text = "修改学生信息";
            treeNode6.Name = "studentMan";
            treeNode6.Text = "学生信息管理";
            treeNode7.Name = "节点3";
            treeNode7.Text = "添加教师信息";
            treeNode8.Name = "节点4";
            treeNode8.Text = "修改教师信息";
            treeNode9.Name = "节点2";
            treeNode9.Text = "教师信息管理";
            treeNode10.Name = "userInfo";
            treeNode10.SelectedImageIndex = 2;
            treeNode10.Text = "用户管理";
            treeNode11.Name = "addCL";
            treeNode11.Text = "审核课程";
            treeNode12.Name = "classMan";
            treeNode12.Text = "课程管理";
            treeNode13.Name = "节点0";
            treeNode13.Text = "修改密码";
            treeNode14.Name = "about";
            treeNode14.Text = "关于";
            treeNode15.Name = "节点0";
            treeNode15.Text = "退出系统";
            this.treeView1.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode10,
            treeNode12,
            treeNode13,
            treeNode14,
            treeNode15});
            this.treeView1.Size = new System.Drawing.Size(167, 434);
            this.treeView1.TabIndex = 1;
            this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
            // 
            // panel2
            // 
            this.panel2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.panel2.Location = new System.Drawing.Point(193, 15);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(650, 435);
            this.panel2.TabIndex = 2;
            // 
            // ManagerTreeview
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(874, 463);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.treeView1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "ManagerTreeview";
            this.Text = "TeacherTreeview";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.Panel panel2;
    }
}