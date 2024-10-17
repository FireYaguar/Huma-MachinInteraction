//Form1.Designer.cs
namespace ESP8266Controller
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.comboBoxPorts = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonLED1 = new System.Windows.Forms.Button();
            this.buttonLED2 = new System.Windows.Forms.Button();
            this.textBoxReceivedData = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // comboBoxPorts
            // 
            this.comboBoxPorts.FormattingEnabled = true;
            this.comboBoxPorts.Location = new System.Drawing.Point(12, 12);
            this.comboBoxPorts.Name = "comboBoxPorts";
            this.comboBoxPorts.Size = new System.Drawing.Size(121, 21);
            this.comboBoxPorts.TabIndex = 0;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(139, 12);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 1;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // buttonLED1
            // 
            this.buttonLED1.Location = new System.Drawing.Point(12, 39);
            this.buttonLED1.Name = "buttonLED1";
            this.buttonLED1.Size = new System.Drawing.Size(75, 23);
            this.buttonLED1.TabIndex = 2;
            this.buttonLED1.Text = "LED 1 ON";
            this.buttonLED1.UseVisualStyleBackColor = true;
            this.buttonLED1.Click += new System.EventHandler(this.buttonLED1_Click);
            // 
            // buttonLED2
            // 
            this.buttonLED2.Location = new System.Drawing.Point(93, 39);
            this.buttonLED2.Name = "buttonLED2";
            this.buttonLED2.Size = new System.Drawing.Size(75, 23);
            this.buttonLED2.TabIndex = 3;
            this.buttonLED2.Text = "LED 2 ON";
            this.buttonLED2.UseVisualStyleBackColor = true;
            this.buttonLED2.Click += new System.EventHandler(this.buttonLED2_Click);
            // 
            // textBoxReceivedData
            // 
            this.textBoxReceivedData.Location = new System.Drawing.Point(12, 68);
            this.textBoxReceivedData.Multiline = true;
            this.textBoxReceivedData.Name = "textBoxReceivedData";
            this.textBoxReceivedData.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxReceivedData.Size = new System.Drawing.Size(260, 181);
            this.textBoxReceivedData.TabIndex = 4;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.textBoxReceivedData);
            this.Controls.Add(this.buttonLED2);
            this.Controls.Add(this.buttonLED1);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.comboBoxPorts);
            this.Name = "Form1";
            this.Text = "ESP8266 Controller";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        private System.Windows.Forms.ComboBox comboBoxPorts;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Button buttonLED1;
        private System.Windows.Forms.Button buttonLED2;
        private System.Windows.Forms.TextBox textBoxReceivedData;
    }
}