class DashboardController < ApplicationController
 
  require 'rubygems'
  require 'ruby-debug'
  # GET /dashboard
  def index
    @protocols = Protocol.find(:all, :conditions => ['name LIKE ?', "%#{params[:search]}%"])
    @page_title = "Firewall Performance Overview"
    session[:avg] = Rate.find(:first).avg_rate
    session[:peak] = Rate.find(:first).peak_rate
    @peak = session[:peak]
    @avg = session[:avg]
    @nav_over = "current"
    @chart = open_flash_chart_object(975,300,"/dashboard/init_chart")

    
    divisor = 1
    data = case session[:interval] 
            when "Seconds"
              divisor =  session[:num].to_i
              Stat.find(:all, :conditions => ["created_at >= ?", Time.now - session[:num].to_i.seconds])
            when "Minutes"
              divisor =  session[:num].to_i * 60
              Stat.find(:all, :conditions => ["created_at >= ?", Time.now - session[:num].to_i.minutes])
            end

    begin
      @traffic_rate_avg =  (data.inject(0){|sum, curr| sum += curr.totalData } /(1024*1024)) /divisor
      @traffic_peak = data.map{|cur| cur.totalData}.max/(1024*1024)/10
      @packets_blocked = data.inject(0){|sum, cur| sum += cur.numDroppedPackets}
      @packets_allowed = data.inject(0){|sum, cur| sum += cur.numPackets} - @packets_blocked
      @percent_good = (@packets_allowed.to_f/data.inject(0){|sum, cur| sum += cur.numPackets}) * 100.0
      @percent_bad = (@packets_blocked.to_f/data.inject(0){|sum, cur| sum += cur.numPackets}) * 100.0
    rescue Exception => e
    end

    respond_to do |format|
      format.html { render :overview }
       # format.html { redirect_to :controller => "users", :action => "new" }
    end
  end
 
  def edit_num
    if ! rate = Rate.find(:first)
      rate = Rate.create
    end

    if params[:editorId] == "avg"
      rate.avg_rate = params[:value].to_f
      session[:avg] = params[:value]
    end

    if params[:editorId] == "peak"
      rate.peak_rate = params[:value].to_f      
      session[:peak] == params[:value]
    end

    rate.save!

    render :update do |page|
      page.reload
    end

  end
 
  # GET /dashboard/ip
  def ip
    @page_title = "IP Configuration"
    @blockeds = Blocked.find(:all, 
                             :select => 'ip, name, port, blockeds.id',
                             :conditions => ['user_id = ?', current_user.id],
                             :joins => :protocols) do #.map do |cur|
   # blockeds = Blocked.all.map do |cur|
    #  debugger
     # blockedsnew = @blockeds.map do |cur|
     # cur.name = $protocol_ids[cur.name.to_i] if cur.name
     # cur
     # end
    if params[:_search] == "true"
      ip =~ "%#{params[:ip]}%" if params[:ip].present?
      protocol =~ "%#{params[:protocol]}%" if params[:protocol].present?
      port =~ "%#{params[:port]}%" if params[:port].present?
      port =~ "%#{params[:id]}%" if params[:id].present?
    end
    paginate :page => params[:page], :per_page => params[:rows]
    order_by "#{params[:sidx]} #{params[:sord]}"
    end

    @blockeds.map do |cur|
      cur.name = $protocol_ids[cur.name.to_i] if cur.name
      cur
    end
    respond_to do |format|
      @nav_ip = "current"
      format.html
      format.json { render :json => @blockeds.to_jqgrid_json([:ip, :name, :port, :id],
                                     params[:page],params[:rows], @blockeds.total_entries) }

      format.js

    end
  end
 
  # DELETE /dashboard/ip/1
  def destroy
    if params[:id]
      Blocked.find(params[:id]).destroy   
    end
 
    respond_to do |format|
      format.html { redirect_to :action => 'ip'  }
      format.xml  { head :ok }
    end
  end
 
  # POST /dashboard
  def create
    @ips = Array.new

    if params[:blocked][:ip2_1] = "" 
      @ips.push((params[:blocked][:ip_1]).to_s + "." + (params[:blocked][:ip_2]).to_s + 
               "." + params[:blocked][:ip_3].to_s + "." + (params[:blocked][:ip_4]).to_s)
    else
      (params[:blocked][:ip_1]..params[:blocked][:ip2_1]).each do |a|
        (params[:blocked][:ip_2]..params[:blocked][:ip2_2]).each do |b|
            (params[:blocked][:ip_3]..params[:blocked][:ip2_3]).each do |c|
               (params[:blocked][:ip_4]..params[:blocked][:ip2_4]).each do |d|
                 @ips.push(a.to_s + "." + b.to_s + "." + c.to_s + "." + d.to_s)
               end
             end
          end
       end
    end
    @ports = Array.new
    if params[:blocked][:port2] = "" 
      @ports.push(params[:blocked][:port].to_s)
    elsif params[:blocked][:port] = "" 
      @ports.push("")
    else
      (params[:blocked][:port]..params[:blocked][:port2]).each do |p|
        @ports.push(p.to_s)
      end
    end
     
    ips_with_ports = (@ips*@ports.size).zip( (@ports*@ips.size).sort )
    blocked = ips_with_ports.map do |ip, port|
      b = Blocked.create(:ip => ip, :port => port, :user_id => current_user.id)
      b.protocols << Protocol.new( :name => $protocol_names[params[:blocked][:protocols].upcase])
      b
   end
    
    respond_to do |format|
      format.html { redirect_to :action => 'ip'  }
    end
  end
 
  # GET /dashboard/protocols
  def protocols
    @page_title = "Protocol Configuration"
    @nav_proto = "current"
    @blocked_protos = Solo_Protocol.find(:all).map { |proto| $protocol_ids[proto.protocol] }
    @allowed_protos = $protocol_names.keys - @blocked_protos
    @blocked_protos << "" 
    @allowed_protos << ""
 
    respond_to do |format|
      format.html
    end
  end
 
  def move_item
    protocol = params[:protocol].split("_")[0]
    list = params[:protocol].split("_")[1]
 
    if list=="blocked"
      Solo_Protocol.new({:protocol => $protocol_names[protocol]}).save!
    else
      Solo_Protocol.find(:all, :conditions => {:protocol => $protocol_names[protocol]}).each {|entry| entry.destroy}
    end
 
    render :update do |page|
      page.remove "protocol_#{protocol}"
      page.insert_html :top, list, render(:partial=>"protocol", :object => protocol)
      page.visual_effect :highlight, "protocol_#{protocol}"
    end
 
  end
 
  def force_update
    msg = Message.new
    msg.msg = "y helo thar"
 
    client = DaemonClient.new
    client.send(msg)
 
    flash[:notice] = "Update Sent!"
    redirect_to :action => "index"
  end
 
  def auto_complete_for_blocked_protocols
    re = Regexp.new("#{params[:blocked][:protocols]}", "i")
    @protos = $protocol_names.keys.reject { |curr| !curr.match re }
    render :inline => "<%= content_tag(:ul, @protos.map { |org| content_tag(:li, h(org)) }) %>"
  end
 
  def chart_scale
    session[:interval] = params[:interval]
    session[:num] = params[:num]
    index
  end

  def reports
    @page_title = "Generate Custom Reports"
    @nav_report = "current"
  end

  def gen_report
    data = case session[:interval] 
            when "Seconds"
              divsor =  session[:num].to_i
              Stat.find(:all, :conditions => ["created_at >= ?", Time.now - session[:num].to_i.seconds])
            when "Minutes"
              divsor =  session[:num].to_i * 60
              Stat.find(:all, :conditions => ["created_at >= ?", Time.now - session[:num].to_i.minutes])
            end

    results ="Timestamp,NumberOfPackets,NumDroppedPackets,TotalData\n"
    results += data.map{|cur| [cur.created_at.to_s, cur.numPackets, cur.numDroppedPackets, cur.totalData].join(",")}.join("\n")

    respond_to do |format|
      format.csv { send_data results, :filename => Time.now.to_s + "_report.csv" }
    end
  end
  
  def init_chart
    title = Title.new("Firewall Traffic Overview")

    session[:num] ||= 30
    session[:interval] ||= "Seconds"
    session[:avg] = Rate.find(:first).avg_rate
    session[:peak] = Rate.find(:first).peak_rate

    data1 = case session[:interval] 
            when "Seconds"
              Stat.find(:all, :conditions => ["created_at >= ?", Time.now - session[:num].to_i.seconds])
            when "Minutes"
              Stat.find(:all, :conditions => ["created_at >= ?", Time.now - session[:num].to_i.minutes])
            end
    data2 = data1.map{|c| c.totalData/(1024*1024)/10}

    line_traffic = Line.new
    line_traffic.text = "Incoming Traffic"
    line_traffic.width = 2
    line_traffic.colour = '#000000'
    line_traffic.values = data2

    line_peak = Line.new
    line_peak.text = "Peak Allowable Traffic"
    line_peak.width = 1
    line_peak.colour = '#FF0000'
    line_peak.values = [session[:peak].to_i] * data2.size

    line_avg = Line.new
    line_avg.text = "Average Allowable Traffic"
    line_avg.width = 1
    line_avg.colour = '#0000FF'
    line_avg.values = [session[:avg].to_i] * data2.size

    y = YAxis.new
    y.set_range(0,[data1.map{|c| c.totalData/(1024 **2)}.max || 0,session[:avg], session[:peak]].max + 5,4)

    x_legend = XLegend.new("Showing the last #{session[:num] + " " + session[:interval]}")
    x_legend.set_style('{font-size: 10px; color: #000000}')

    y_legend = YLegend.new("mbps")
    y_legend.set_style('{font-size: 10px; color: #000000}')

    chart =OpenFlashChart.new
    chart.set_title(title)

    chart.set_x_legend(x_legend)
    chart.set_y_legend(y_legend)
    chart.y_axis = y

    chart.add_element(line_traffic)
    chart.add_element(line_peak)
    chart.add_element(line_avg)

    render :text => chart.to_s
  end
 
end
